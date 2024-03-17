#include <DHT11.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define pinoUmidade A2
#define pinoLDR A1
#define pinoTMP 2
#define pinoReleLmpd 7
#define pinoReleFan 8

const int JANELA = 5;
const int SETPOINT_LUM = 50;
const float SETPOINT_TEMP = 27.0;

float _somaTemp = 0.0;
int _somaUmi = 0;
int _somaLum = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT11 dht11(pinoTMP);

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinoReleLmpd, OUTPUT);
  pinMode(pinoReleFan, OUTPUT);
  pinMode(pinoUmidade, INPUT);
  pinMode(pinoLDR, INPUT);
  pinMode(pinoTMP, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
}

void loop() {
  float temperatura = 0;
  int umidade = 0;
  int luminosidade = 0;

  for(int i = 0; i < JANELA; i++) {
    temperatura = dht11.readTemperature();
    umidade = calcUmidade();
    luminosidade = calcLum();

    printDisplay(temperatura, umidade, luminosidade);

    mediaMovel(&temperatura, &umidade, &luminosidade, i);

    delay(1000);
  }

  controlaVar(temperatura, luminosidade);

  mandaMensagem(temperatura, umidade, luminosidade);
}

int calcUmidade() {
  return map(analogRead(pinoUmidade), 1023, 315, 0, 100);
}

int calcLum() {
  return map(analogRead(pinoLDR), 1023, 0, 0, 100);
}

void mediaMovel(float* temperatura, int* umidade, int* luminosidade, int i) {
  _somaTemp += *temperatura;
  _somaUmi += *umidade;
  _somaLum += *luminosidade;

  if((i+1) == JANELA) {
    *temperatura = _somaTemp/JANELA;
    *umidade = _somaUmi/JANELA;
    *luminosidade = _somaLum/JANELA;
    _mediaMovelClear();
  }
}

void _mediaMovelClear() {
  _somaTemp = 0.0;
  _somaUmi = 0;
  _somaLum = 0;
}

void controlaVar(float temperatura, int luminosidade) {
  _ligaFan(temperatura);
  _acendeLmpd(luminosidade);
}

void _acendeLmpd(int luminosidade) {
  if(luminosidade < SETPOINT_LUM) 
    digitalWrite(pinoReleLmpd, HIGH);
  else 
    digitalWrite(pinoReleLmpd, LOW);
}

void _ligaFan(float temperatura) {
  if(temperatura > SETPOINT_TEMP) 
    digitalWrite(pinoReleFan, HIGH);
  else 
    digitalWrite(pinoReleFan, LOW);
}

void mandaMensagem(float temperatura, int umidade, int luminosidade) {
  Serial.print(String(umidade) + "," + String(temperatura) + "," + String(luminosidade));
}

void printDisplay(float temperatura, int umidade, int luminosidade) {
    display.clearDisplay();
    display.display();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0); display.println("CLIMATICA TECH"); display.display();
    display.println("Temperatura: " + String(temperatura) + " C"); display.display();
    display.println("Umidade: " + String(umidade) + "%"); display.display();
    display.println("Luminosidade: " + String(luminosidade) + "%"); display.display();
}
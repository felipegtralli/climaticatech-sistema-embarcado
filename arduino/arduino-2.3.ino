#include <ClimaticaTech_Controle_Var.h>
#include <ClimaticaTech_Filtro.h>
#include <ClimaticaTech_Mede_Var.h>
#include <ClimaticaTech_Msg.h>
#include <ClimaticaTech_Display.h>

#define pinoUmidade A2
#define pinoLDR A1
#define pinoTMP 3
#define pinoReleLmpd 6
#define pinoReleBomba 7
#define pinoPWMFan 9

const int JANELA = 5;
const int SETPOINT_UMI = 50;
const int SETPOINT_LUM = 50;
const double SETPOINT_TEMP = 20.0;

ClimaticaTech_ControleVar controle(pinoReleBomba, pinoReleLmpd, pinoPWMFan, SETPOINT_UMI, SETPOINT_LUM, SETPOINT_TEMP);
ClimaticaTech_Filtro filtro(JANELA);
ClimaticaTech_MedeVar medeVar(pinoUmidade, pinoLDR, pinoTMP);
ClimaticaTech_Display display;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(pinoReleLmpd, OUTPUT);
  pinMode(pinoReleBomba, OUTPUT);
  pinMode(pinoPWMFan, OUTPUT);
  
  pinMode(pinoUmidade, INPUT);
  pinMode(pinoLDR, INPUT);
  pinMode(pinoTMP, INPUT);

  digitalWrite(pinoReleLmpd, LOW);
  digitalWrite(pinoReleBomba, LOW);

  display.begin();
}

void loop() {
  int umidade = 0;
  int luminosidade = 0;
  double temperatura = 0.0;

  for(int i = 0; i < JANELA; i++) {
    medeVar.medir(&umidade, &luminosidade, &temperatura);

    display.print(umidade, luminosidade, temperatura);

    filtro.mediaMovel(&umidade, &luminosidade, &temperatura, i);

    delay(1000);
  }

  controle.controlar(umidade, luminosidade, temperatura);

  ClimaticaTech_Msg::mandaMensagem(umidade, luminosidade, temperatura);
}
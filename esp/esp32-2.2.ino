#include <ClimaticaTech_Wifi.h>
#include <ClimaticaTech_Http.h>
#include <ClimaticaTech_Msg_esp.h>

#define RXp2 16
#define TXp2 17

const char* SSID = "";
const char* PASSWORD = "";
const char* URL = "";
const char* API_KEY = "";

ClimaticaTech_Wifi wifi((char*)SSID, (char*)PASSWORD);
ClimaticaTech_Http http((char*)URL, (char*)API_KEY);

void setup() {
 Serial.begin(115200);
 Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

 wifi.connectWifi();
}

void loop() {
  if(!wifi.isConnected())
    wifi.connectWifi();

  String umidade;
  String temperatura;
  String luminosidade;
  
  ClimaticaTech_Msg_esp::recebeMensagem(&umidade, &temperatura, &luminosidade);

  http.mandaDados(umidade, temperatura, luminosidade);
}
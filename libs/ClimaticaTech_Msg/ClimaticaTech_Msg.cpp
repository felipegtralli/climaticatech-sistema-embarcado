#include "ClimaticaTech_Msg.h"
#include <Arduino.h>

void ClimaticaTech_Msg::mandaMensagem(int umidade, int luminosidade, double temperatura) {
  Serial.print(String(umidade) + "," + String(temperatura) + "," + String(luminosidade));
}
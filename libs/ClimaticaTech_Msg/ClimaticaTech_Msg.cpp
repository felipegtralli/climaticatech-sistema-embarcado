#include "ClimaticaTech_Msg.h"
#include <Arduino.h>

void ClimaticaTech_Msg::mandaMensagem(int umidade, int luminosidade, float temperatura) {
  Serial.print(String(umidade) + "," + String(temperatura) + "," + String(luminosidade));
}
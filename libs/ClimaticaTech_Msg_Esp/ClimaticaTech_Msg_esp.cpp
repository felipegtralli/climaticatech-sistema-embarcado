#include "ClimaticaTech_Msg_esp.h"
#include <Arduino.h>

void ClimaticaTech_Msg_esp::recebeMensagem(String* umidade, String* luminosidade, String* temperatura) {
  String msgRecebida = "";

  while(msgRecebida.isEmpty()) {
    msgRecebida = Serial2.readString();
  }

  ClimaticaTech_Msg_esp::stringSplit(msgRecebida, umidade, luminosidade, temperatura);
}

void ClimaticaTech_Msg_esp::stringSplit(String m, String* umidade, String* luminosidade, String* temperatura) {
  char* p;
  char msg[m.length() + 1];
  p = strtok(strcpy(msg, m.c_str()), ",");
  
  int i = 0;
  while(p != NULL && p != "\n") {
    String s = p;

    switch(i) {
      case 0:
        *umidade = s;
        break;
      case 1:
        *temperatura = s;
        break;
      case 2:
        *luminosidade = s;
        break;
    }

    p = strtok(NULL, ",");
    i++;
  }
}
#ifndef ClimaticaTech_Msg_esp_h
#define ClimaticaTech_Msg_esp_h

#include <Arduino.h>

class ClimaticaTech_Msg_esp {
public:
    static void recebeMensagem(String* umidade, String* luminosidade, String* temperatura);

private:
    static void stringSplit(String m, String* umidade, String* temperatura, String* luminosidade);
};

#endif
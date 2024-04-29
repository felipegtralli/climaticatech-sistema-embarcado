#ifndef ClimaticaTech_Mede_Var_h
#define ClimaticaTech_Mede_Var_h

#include <DHT11.h>

class ClimaticaTech_MedeVar {
private:
    int pin_umidade;
    int pin_luminosidade;
    DHT11* dht11;

public:
    ClimaticaTech_MedeVar(int pin_umidade, int pin_luminosidade, int pin_temperatura);
    void medir(int* umidade, int* luminosidade, double* temperatura);

private:
    int calculaUmidade();
    int calculaLuminosidade();
    int calculaTemperatura();
};


#endif

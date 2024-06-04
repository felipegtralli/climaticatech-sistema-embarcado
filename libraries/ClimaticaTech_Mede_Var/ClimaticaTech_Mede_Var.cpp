#include "ClimaticaTech_Mede_Var.h"
#include <Arduino.h>
#include <DHT11.h>

ClimaticaTech_MedeVar::ClimaticaTech_MedeVar(int pin_umidade, int pin_luminosidade, int pin_temperatura) {
    this->pin_umidade = pin_umidade;
    this->pin_luminosidade = pin_luminosidade;
    dht11 = new DHT11(pin_temperatura);
}

void ClimaticaTech_MedeVar::medir(int* umidade, int* luminosidade, double* temperatura) {
    *umidade = calculaUmidade();
    *luminosidade = calculaLuminosidade();
    *temperatura = (double)calculaTemperatura();
}

int ClimaticaTech_MedeVar::calculaUmidade() {
    return map(analogRead(pin_umidade), 1023, 315, 0, 100);
}

int ClimaticaTech_MedeVar::calculaLuminosidade() {
    return map(analogRead(pin_luminosidade), 1023, 0, 0, 100);
}

int ClimaticaTech_MedeVar::calculaTemperatura() {
    return (*dht11).readTemperature();
}
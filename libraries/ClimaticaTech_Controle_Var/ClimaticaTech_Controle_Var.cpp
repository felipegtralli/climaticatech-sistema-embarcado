#include <Arduino.h>
#include <PID_v1.h>
#include "ClimaticaTech_Controle_Var.h"

ClimaticaTech_ControleVar::ClimaticaTech_ControleVar(int pin_umidade, int pin_luminosidade, int pin_temperatura, 
                int setpoint_umidade, int setpoint_luminosidade, double setpoint_temperatura) {
    
    this->pin_umidade = pin_umidade;
    this->pin_luminosidade = pin_luminosidade;
    this->pin_temperatura = pin_temperatura;
    this->setpoint_umidade = setpoint_luminosidade;
    this->setpoint_luminosidade = setpoint_luminosidade;
    this->setpoint_temperatura = setpoint_temperatura;
    this->pid = new PID(&temp, &comando, &setpoint_temperatura, 2, 5, 2, REVERSE);

    (*pid).SetMode(AUTOMATIC);
}

void ClimaticaTech_ControleVar::controlar(int umidade, int luminosidade, double temperatura) {
    controlaUmidade(umidade);
    controlaLuminosidade(luminosidade);
    controlaTemperatura(temperatura);
}

void ClimaticaTech_ControleVar::controlaUmidade(int umidade) {
    if(!(umidade < setpoint_umidade))
        digitalWrite(pin_umidade, HIGH);
    else
        digitalWrite(pin_umidade, LOW);
}

void ClimaticaTech_ControleVar::controlaLuminosidade(int luminosidade) {
    if(!(luminosidade < setpoint_luminosidade))
        digitalWrite(pin_luminosidade, HIGH);
    else
        digitalWrite(pin_luminosidade, LOW);
}

void ClimaticaTech_ControleVar::controlaTemperatura(double temperatura) {
    temp = temperatura;

    (*pid).Compute();

    analogWrite(pin_temperatura, comando);
}
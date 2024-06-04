#ifndef ClimaticaTech_Controle_Var_h
#define ClimaticaTech_Controle_Var_h

#include <PID_v1.h>

class ClimaticaTech_ControleVar {
private:
    int pin_umidade;
    int pin_luminosidade;
    int pin_temperatura;
    int setpoint_umidade;
    int setpoint_luminosidade;
    float setpoint_temperatura;

    PID* pid;
    double temp;
    double comando;

public:
    ClimaticaTech_ControleVar(int pin_umidade, int pin_luminosidade, int pin_temperatura, 
                int setpoint_umidade, int setpoint_luminosidade, double setpoint_temperatura);
                
    void controlar(int umidade, int luminosidade, double temperatura);

private:
    void controlaUmidade(int umidade);
    void controlaLuminosidade(int luminosidade);
    void controlaTemperatura(double temperatura);

    void printPID();
};

#endif
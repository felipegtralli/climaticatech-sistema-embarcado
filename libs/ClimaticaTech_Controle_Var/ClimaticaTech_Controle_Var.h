#ifndef ClimaticaTech_Controle_Var_h
#define ClimaticaTech_Controle_Var_h

class ClimaticaTech_ControleVar {
private:
    int pin_umidade;
    int pin_luminosidade;
    int pin_temperatura;
    int setpoint_umidade;
    int setpoint_luminosidade;
    float setpoint_temperatura;

public:
    ClimaticaTech_ControleVar(int pin_umidade, int pin_luminosidade, int pin_temperatura, 
                int setpoint_umidade, int setpoint_luminosidade, float setpoint_temperatura);
                
    void controlar(int umidade, int luminosidade, float temperatura);

private:
    void controlaUmidade(int umidade);
    void controlaLuminosidade(int luminosidade);
    // pid todo
    void controlaTemperatura(float temperatura);
};

#endif
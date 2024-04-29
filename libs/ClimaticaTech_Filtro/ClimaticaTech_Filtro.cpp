#include "ClimaticaTech_Filtro.h"

ClimaticaTech_Filtro::ClimaticaTech_Filtro(int janela) {
    this->janela = janela;
    soma_luminosidade = soma_umidade = 0;
    soma_temperatura = 0.0;
}

void ClimaticaTech_Filtro::mediaMovel(int* umidade, int* luminosidade, double* temperatura, int itr) {
    soma_umidade += *umidade;
    soma_luminosidade += *luminosidade;
    soma_temperatura += *temperatura;

    if((itr+1) == janela) {
        *umidade = soma_umidade/janela;
        *luminosidade = soma_luminosidade/janela;
        *temperatura = soma_temperatura/janela;
        mediaMovelHelper();
    }   
}

void ClimaticaTech_Filtro::mediaMovelHelper() {
    this->soma_umidade = this->soma_luminosidade = 0;
    this->soma_temperatura = 0.0;
}

#ifndef ClimaticaTech_Filtro_h
#define ClimaticaTech_Filtro_h

class ClimaticaTech_Filtro {
private:
    int janela;
    int soma_umidade = 0;
    int soma_luminosidade = 0;
    float soma_temperatura = 0.0;

public:
    ClimaticaTech_Filtro(int janela);
    void mediaMovel(int* umidade, int* luminosidade, float* temperatura, int itr);

private:
    void mediaMovelHelper();
};

#endif
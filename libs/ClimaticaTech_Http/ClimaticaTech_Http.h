#ifndef ClimaticaTech_Http_h
#define ClimaticaTech_Http_h

#include <HTTPClient.h>
#include <Arduino.h>

class ClimaticaTech_Http {
private:
    char* url;
    HTTPClient* http;

public:
    ClimaticaTech_Http(char* url, char* api_key);
    void mandaDados(String umidade, String luminosidade, String temperatura);

private:
    static String postData(String umidade, String luminosidade, String temperatura);
    void printResponse(String umidade, String luminosidade, String temperatura, int responde_code, String payload);
};

#endif
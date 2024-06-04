#include "ClimaticaTech_Http.h"
#include <HTTPClient.h>
#include <Arduino.h>

ClimaticaTech_Http::ClimaticaTech_Http(char* url, char* api_key) {
    this->url = url;
    http = new HTTPClient;

    (*http).begin(url);
    (*http).addHeader("Content-Type", "application/json");
    (*http).addHeader("X-API-KEY", api_key);
}

void ClimaticaTech_Http::mandaDados(String umidade, String luminosidade, String temperatura) {
    int httpCode = (*http).POST(postData(umidade, luminosidade, temperatura));
    String payload = (*http).getString();

    ClimaticaTech_Http::printResponse(umidade, luminosidade, temperatura, httpCode, payload);
}

String ClimaticaTech_Http::postData(String umidade, String luminosidade, String temperatura) {
    return "{\"umidade\":\"" + umidade + "\", \"temperatura\":\"" + temperatura + "\", \"luminosidade\":\"" + luminosidade + "\"}";
}

void ClimaticaTech_Http::printResponse(String umidade, String luminosidade, String temperatura, int responde_code, String payload) {
    Serial.printf("Dados: Umidade: %s%%     Temperatura: %s *C     Luminosidade: %s%%\n", umidade, temperatura, luminosidade);
    Serial.printf("URL : %s\n", url);
    Serial.printf("httpCode: %d\n", responde_code); 
    Serial.println("payload : " + String(payload));
    Serial.println("--------------------------------------------------");
}
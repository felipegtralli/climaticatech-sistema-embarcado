#include "ClimaticaTech_Wifi.h"
#include <WiFi.h>
#include <Arduino.h>

ClimaticaTech_Wifi::ClimaticaTech_Wifi(char *ssid, char *password) {
    this->ssid = ssid;
    this->password = password;
}

void ClimaticaTech_Wifi::connectWifi() {
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");

    while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    
    Serial.println("\nconnected to : " + String(ssid));
    Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

bool ClimaticaTech_Wifi::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
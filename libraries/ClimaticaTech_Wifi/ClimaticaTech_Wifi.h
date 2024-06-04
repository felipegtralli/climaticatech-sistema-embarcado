#ifndef ClimaticaTech_Wifi_h
#define ClimaticaTech_Wifi_h

class ClimaticaTech_Wifi {
private:
    char* ssid;
    char* password;

public:
    ClimaticaTech_Wifi(char* ssid, char* password);
    void connectWifi();
    bool isConnected();
};

#endif
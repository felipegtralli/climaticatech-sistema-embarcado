#ifndef ClimaticaTech_Display_h
#define ClimaticaTech_Display_h

#include <Adafruit_SSD1306.h>

class ClimaticaTech_Display {
private:
    Adafruit_SSD1306* display;

public:
    ClimaticaTech_Display();
    void begin();
    void print(int umidade, int luminosidade, double temperatura);
};

#endif
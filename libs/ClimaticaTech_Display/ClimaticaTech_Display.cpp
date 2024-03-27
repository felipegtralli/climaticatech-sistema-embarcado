#include "ClimaticaTech_Display.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

ClimaticaTech_Display::ClimaticaTech_Display() {
    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

void ClimaticaTech_Display::begin() {
    (*display).begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    (*display).setTextColor(SSD1306_WHITE);
    (*display).setTextSize(1);
    (*display).clearDisplay();
}

void ClimaticaTech_Display::print(int umidade, int luminosidade, float temperatura) {
    (*display).clearDisplay();
    (*display).setCursor(0, 0);

    (*display).println("CLIMATICA TECH");
    (*display).println("Temperatura: " + String(temperatura) + " C");
    (*display).println("Umidade: " + String(umidade) + "%");
    (*display).println("Luminosidade: " + String(luminosidade) + "%");

    (*display).display();
}
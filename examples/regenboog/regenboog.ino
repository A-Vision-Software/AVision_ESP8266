/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Arduino 8x8 dot-matrix en WS2812 RGB kleuren LEDs
*
* Created by       :        Arnold Velzel
* Created on       :        11-10-2021
*
*******************************************************************************/

// Definities
#define DEBUG_ENABLED   true

#define DISPLAY_ROWS            1
#define DISPLAY_COLUMNS         1
#define DISPLAY_HARDWARE_TYPE   MD_MAX72XX::PAROLA_HW
#define BUTTON1                 D5

#include "avision_debug.h"
#include "avision_RGBleds.h"
#include "avision_display.h"

// https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h
AVision::RGBleds leds; // RGB Din => D3
// Maak display object
AVision::dotmatrixDisplay display;

void setup()
{
    // https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
    pinMode(BUTTON1, INPUT_PULLUP);

    initDebug(DEBUG_ENABLED);
    display.init(DISPLAY_ROWS, DISPLAY_COLUMNS);
    leds.setLEDcount(8);
    leds.setLEDtype(NEO_GRB);
    leds.init();

    // Kleuren -> Rood, Groen, Blauw, Wit
    // Waarden -> o is uit, 255 is maximaal
    uint32_t red = leds.color(255, 0, 0, 0);
    uint32_t orange = leds.color(255, 64, 0, 0);
    uint32_t yellow = leds.color(255, 255, 0, 0);
    uint32_t green = leds.color(0, 255, 0, 0);
    uint32_t cyan = leds.color(0, 255, 255, 0);
    uint32_t blue = leds.color(0, 0, 255, 0);
    uint32_t purple = leds.color(255, 0, 255, 0);
    uint32_t white = leds.color(0, 0, 0, 255);

    leds.setLED(0, orange);
    leds.setLED(1, yellow);
    leds.setLED(2, green);
    leds.setLED(3, blue);

    leds.setLED(4, yellow);
    leds.setLED(5, green);
    leds.setLED(6, blue);
    leds.setLED(7, purple);

    // Licht helderheid in procenten 0% - 100%
    leds.setBrightness(100);
    leds.loop();

    display.setRow(0, 0x3f);
    display.setRow(1, 0x3f);
    display.setRow(2, 0x1f);
    display.setRow(3, 0x1f);
    display.setRow(4, 0x0f);
    display.setRow(5, 0x03);
}

void loop()
{
}

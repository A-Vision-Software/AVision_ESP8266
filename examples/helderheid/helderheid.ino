/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Arduino WS2812 RGB LED helderheid test
*
* Created by       :        Arnold Velzel
* Created on       :        08-10-2021
*
*******************************************************************************/

#define DEBUG_ENABLED       true

#define ANALOG_INPUT        A0
#define MAX_ANALOG_VALUE    1023

#include "avision_debug.h"
#include "avision_RGBleds.h"

// https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h
AVision::RGBleds leds; // RGB Din => D3

void setup()
{
    initDebug(DEBUG_ENABLED);
    leds.setLEDcount(8);
    leds.setLEDtype(NEO_GRB);
    leds.init();

    // Kleuren -> Rood, Groen, Blauw, Wit
    // Waarden -> 0 is uit, 255 is maximaal
    uint32_t red = leds.color(128, 0, 0, 0);
    uint32_t green = leds.color(0, 128, 0, 0);
    uint32_t blue = leds.color(0, 0, 128, 0);
    uint32_t white = leds.color(0, 0, 0, 128);
    uint32_t bright_white = leds.color(255, 255, 255, 255);

    leds.setLED(0, red);
    leds.setLED(1, green);
    leds.setLED(2, blue);
    leds.setLED(3, white);

    leds.setLED(4, bright_white);
    leds.setLED(5, bright_white);
    leds.setLED(6, bright_white);
    leds.setLED(7, bright_white);

    // Licht helderheid in procenten 0% - 100%
    leds.setBrightness(100);
}

void loop()
{
    // https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
    int level = 100 * analogRead(ANALOG_INPUT) / MAX_ANALOG_VALUE;
    leds.setBrightness(level);
    leds.loop();
}

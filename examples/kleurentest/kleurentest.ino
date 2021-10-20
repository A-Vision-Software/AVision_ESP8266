/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Arduino WS2812 RGB kleuren LED combineren test
*
* Created by       :        Arnold Velzel
* Created on       :        08-10-2021
*
*******************************************************************************/
#include <Adafruit_NeoPixel.h>

#define DEBUG_ENABLED   true

#define BUTTON1         D5
#define BUTTON2         D6
#define BUTTON3         D7
#define BUTTON4         D0

#define LED_DIN_PIN     D3
#define LED_TYPE        NEO_GRB
#define LED_COUNT       8

#include "avision_debug.h"
#include "avision_RGBleds.h"

// https://github.com/adafruit/Adafruit_NeoPixel/blob/master/Adafruit_NeoPixel.h
AVision::RGBleds leds(LED_DIN_PIN); // RGB Din => D3

// Kleuren -> Rood, Groen, Blauw, Wit
// Waarden -> 0 is uit, 255 is maximaal
uint32_t red    = leds.color(128, 0, 0, 0);
uint32_t green  = leds.color(0, 128, 0, 0);
uint32_t blue   = leds.color(0, 0, 128, 0);
uint32_t white  = leds.color(0, 0, 0, 128);

void setup()
{
    // https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
    pinMode(BUTTON4, INPUT_PULLUP);

    initDebug(DEBUG_ENABLED);
    leds.setLEDcount(LED_COUNT);
    leds.setLEDtype(LED_TYPE);
    leds.init();

    // Licht helderheid in procenten 0% - 100%
    leds.setBrightness(100);
    leds.loop();
}

void loop()
{
    uint32_t combined = leds.color(0, 0, 0, 0); // All off

    // https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
    if (digitalRead(BUTTON1) == LOW) {
        combined += red;
    }
    if (digitalRead(BUTTON2) == LOW) {
        combined += green;
    }
    if (digitalRead(BUTTON3) == LOW) {
        combined += blue;
    }
    if (digitalRead(BUTTON4) == LOW) {
        combined += white;
    }

    leds.setLED(0, red);
    leds.setLED(1, green);
    leds.setLED(2, blue);
    leds.setLED(3, white);

    leds.setLED(4, combined);
    leds.setLED(5, combined);
    leds.setLED(6, combined);
    leds.setLED(7, combined);

    leds.loop();

    delay(50);
}

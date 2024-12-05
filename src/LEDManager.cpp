#include "LEDManager.h"

#include <Adafruit_NeoPixel.h>

#define LED_PIN 42
#define LED_PWR 37
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void LEDSetup() {
  pinMode(LED_PWR, OUTPUT);
  digitalWrite(LED_PWR, LOW);
  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();   // Turn OFF all pixels ASAP
}

void setLEDColor(byte r, byte g, byte b) {
  strip.setPixelColor(0, r, g, b);
  strip.show();
}
#include <Arduino.h>

#include "LEDManager.h"
#include "RadioManager.h"
#include "TimeManager.h"

void setup() {
  LEDSetup();
  // while (!Serial) {
  //   setLEDColor(0, 0, 200);
  //   delay(500);
  //   setLEDColor(0, 0, 0);
  //   delay(500);
  // }
  // delay(500);

  timeManager.init();
  radioManager.init();
}

void loop() {
  timeManager.update();
  radioManager.update();
}

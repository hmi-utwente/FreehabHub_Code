#include <Arduino.h>

#include "LEDManager.h"
#include "RadioManager.h"
#include "SerialManager.h"
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

  serialManager.init();
  timeManager.init();
  radioManager.init();
}

void loop() {
  serialManager.update();
  timeManager.update();
  radioManager.update();
}

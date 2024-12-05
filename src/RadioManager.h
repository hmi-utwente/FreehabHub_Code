#pragma once
#include <Arduino.h>
#include <elapsedMillis.h>

class RadioManager {
 public:
  void init();
  void update();

 private:
  elapsedMillis sinceSend = 999999;
};

extern RadioManager radioManager;
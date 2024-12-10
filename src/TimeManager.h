#pragma once
#include <Arduino.h>
#include <elapsedMillis.h>

class TimeManager {
 public:
  void init();
  void update();

  unsigned long getTime();
  void setTime(unsigned long t);

 private:
  elapsedMillis sincePrint;
};

extern TimeManager timeManager;
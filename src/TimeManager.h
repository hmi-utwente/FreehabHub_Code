#pragma once
#include <Arduino.h>
#include <elapsedMillis.h>

class TimeManager {
 public:
  void init();
  void update();
  String getTimeString();

  unsigned long getTime();
  void setTime(unsigned long t);

 private:
  void wakeup_reason();
  elapsedMillis sincePrint;
};

extern TimeManager timeManager;
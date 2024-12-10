#include "TimeManager.h"

#include <RTClib.h>
#include <SPI.h>

RTC_DS3231 rtc;

void TimeManager::init() {
  Wire.begin(1, 2);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void TimeManager::update() {
  if (sincePrint < 1000) return;
  sincePrint = 0;
  DateTime now = rtc.now();
  Serial.printf("%.4i-%.2i-%.2i %.2i:%.2i:%.2i\r\n", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
}

unsigned long TimeManager::getTime() {
  return rtc.now().unixtime();
}

void TimeManager::setTime(unsigned long t) {
  rtc.adjust(DateTime(t));
}

TimeManager timeManager;
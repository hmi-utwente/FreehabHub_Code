#include "TimeManager.h"

#include <ESP32Time.h>

ESP32Time rtc;

void TimeManager::init() {
  wakeup_reason();

  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));  // (String) returns time with specified format
}

void TimeManager::update() {
  if (sincePrint < 1000) return;
  sincePrint = 0;
  Serial.println(getTimeString());
}

String TimeManager::getTimeString() {
  return rtc.getTime("%Y_%m_%d_%H_%M_%S");
}

unsigned long TimeManager::getTime() {
  return rtc.getEpoch();
}

void TimeManager::setTime(unsigned long t) {
  rtc.setTime(t);
}

void TimeManager::wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Wakeup caused by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Wakeup caused by external signal using RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Wakeup caused by timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Wakeup caused by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Wakeup caused by ULP program");
      break;
    default:
      Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
      rtc.setTime(30, 24, 15, 17, 1, 2021);  // TODO; set to last saved date on from SD

      break;
  }
}

TimeManager timeManager;
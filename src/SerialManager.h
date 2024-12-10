#pragma once
#include <Arduino.h>

class SerialManager {
 public:
  void init();
  void update();

 private:
  void parseInput();
  static const int MAX_INPUT_SIZE = 64;  // Maximum number of characters for the input
  char inputString[MAX_INPUT_SIZE];      // Character array to hold the incoming data
  int inputIndex = 0;                    // Index for storing characters in the array
};

extern SerialManager serialManager;
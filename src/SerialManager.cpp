#include "SerialManager.h"

#include "TimeManager.h"
#include "config.h"

void SerialManager::init() {
}

void SerialManager::update() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();  // Read the next character

    // If newline character is received, mark newData as true
    if (incomingChar == '\n') {
      inputString[inputIndex] = '\0';  // Null-terminate the string
      parseInput();
    } else {
      // If there's room in the buffer, add the character
      if (inputIndex < MAX_INPUT_SIZE - 1) {
        inputString[inputIndex] = incomingChar;
        inputIndex++;
      }
    }
  }
}

void SerialManager::parseInput() {
  unsigned long parsedValue = strtoul(inputString, NULL, 10);  // Convert the C string to an integer

  // Display the parsed integer
  Serial.print("Parsed Integer: ");
  Serial.println(parsedValue);
  if (parsedValue > 1733841333)
    timeManager.setTime(parsedValue);

  // Clear the input buffer and reset the index and newData flag
  inputIndex = 0;
}

SerialManager serialManager;
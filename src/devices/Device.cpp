#include <Arduino.h>
#include "./Device.h"

Device::Device(unsigned char _pin) : pin(_pin) {};

void Device::makeOutputInverted() {
  isOutputInverted = true;
}

void Device::writeToPin() {
  bool pinValue;

  if (isEnabled) {
    pinValue = isOutputInverted ? LOW : HIGH;
  } else {
    pinValue = isOutputInverted ? HIGH : LOW;
  }
  digitalWrite(pin, pinValue);
}

void Device::init() {
  pinMode(pin, OUTPUT);

  if (isOutputInverted) {
    writeToPin();
  }
}
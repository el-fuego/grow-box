#include <Arduino.h>
#include "./Device.h"

Device::Device(unsigned char _pin) : pin(_pin) {
  isEnabled = false;
};

void Device::writeToPin() {
  digitalWrite(pin, isEnabled ? HIGH : LOW);
}
void Device::writeToPinInverted() {
  digitalWrite(pin, isEnabled ? LOW : HIGH);
}

void Device::init() {
  pinMode(pin, OUTPUT);
}
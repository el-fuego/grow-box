#include <Arduino.h>
#include "./BaseRelay.h"


BaseRelay::BaseRelay(unsigned char _pin, unsigned int &_demandedValue, unsigned char &_currentValue) : Device(_pin), demandedValue(_demandedValue), currentValue(_currentValue) {};

void BaseRelay::writeToPin() {
  Device::writeToPin();
  toggledAt = millis();
};

bool BaseRelay::canMeasure() {
  return toggledAt == 0 || abs(millis() - toggledAt) > minMeasureInterval;
};

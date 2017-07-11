#include <Arduino.h>
#include "./IntensityControl.h"

const unsigned char MAX_VALUE = 255;

IntensityControl::IntensityControl(unsigned char _pin, unsigned int &_percentage) : Device(_pin), percentage(_percentage) {};
IntensityControl::IntensityControl(unsigned char _pin, unsigned int &_percentage, unsigned int _rangeStart) : Device(_pin), percentage(_percentage), rangeStart(_rangeStart) {};

unsigned int IntensityControl::getPinValue() {
  return (rangeStart + percentage * (100 - rangeStart) / 100) * MAX_VALUE / 100;
}

void IntensityControl::update() {
  if (previousPercentage != percentage) {
    isEnabled = percentage > 0;
    analogWrite(pin, isEnabled ? getPinValue() : 0);

    previousPercentage = percentage;
  }
};
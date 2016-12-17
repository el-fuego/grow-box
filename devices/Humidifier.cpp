#include <Arduino.h>
#include "./Humidifier.h"

Humidifier::Humidifier(unsigned char _pin, unsigned int &_demandedHumidity, unsigned char &_currentHumidity) : Device(_pin), demandedHumidity(_demandedHumidity), currentHumidity(_currentHumidity) {};
    
void Humidifier::update() {
  if (isEnabled && currentHumidity > demandedHumidity + minDifference) {
    isEnabled = false;
    writeToPin();
  }
  if (!isEnabled && currentHumidity < demandedHumidity - minDifference) {
    isEnabled = true;
    writeToPin();
  }
};

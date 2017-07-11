#include <Arduino.h>
#include "./TurnOnWhenHigher.h"


void TurnOnWhenHigher::update() {
  if (!isEnabled && currentValue > demandedValue + minDifference) {
    isEnabled = true;
    writeToPin();
  }
  if (isEnabled && currentValue < demandedValue) {
    isEnabled = false;
    writeToPin();
  }
};

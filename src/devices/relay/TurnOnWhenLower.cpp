#include <Arduino.h>
#include "./TurnOnWhenLower.h"


void TurnOnWhenLower::update() {
  if (!canMeasure()) {
    return;
  }

  if (!isEnabled && currentValue < demandedValue - minDifference) {
    isEnabled = true;
    writeToPin();
  }
  if (isEnabled && currentValue > demandedValue) {
    isEnabled = false;
    writeToPin();
  }
};

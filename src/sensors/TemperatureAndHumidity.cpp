#include "./TemperatureAndHumidity.h"

#define UPDATE_INTERVAL 1000


TemperatureAndHumidity::TemperatureAndHumidity(unsigned char _pin) : pin(_pin) {};

void TemperatureAndHumidity::init() {};

void TemperatureAndHumidity::update() {
  unsigned long currentMillis = millis();
  if (currentMillis < updatedAt) {
  	updatedAt = 0;
  }
  if (currentMillis - updatedAt < UPDATE_INTERVAL) {
    return;
  }

  updatedAt = currentMillis;
  hasError = driver.read(pin, &temperature, &humidity, NULL);
};


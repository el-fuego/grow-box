
#include "./TemperatureAndHumidity.h"

TemperatureAndHumidity::TemperatureAndHumidity(unsigned char _pin) : pin(_pin) {};

void TemperatureAndHumidity::init() {};

void TemperatureAndHumidity::update() {
  hasError = driver.read(pin, &temperature, &humidity, NULL);
};


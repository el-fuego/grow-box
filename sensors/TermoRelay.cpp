
#include <Arduino.h>
#include "./TermoRelay.h"

TermoRelay::TermoRelay(unsigned char _pin, unsigned char _limitValue) : pin(_pin), limitValue(_limitValue) {};

void TermoRelay::init() {
  pinMode(pin, INPUT);
};

void TermoRelay::update() {
  isEnabled = analogRead(pin) > limitValue;
};


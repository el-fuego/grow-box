#include <Arduino.h>
#include "./BaseRelay.h"


BaseRelay::BaseRelay(unsigned char _pin, unsigned int &_demandedValue, unsigned char &_currentValue) : Device(_pin), demandedValue(_demandedValue), currentValue(_currentValue) {};

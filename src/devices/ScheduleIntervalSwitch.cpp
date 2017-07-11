#include <Arduino.h>
#include "./ScheduleIntervalSwitch.h"

ScheduleIntervalSwitch::ScheduleIntervalSwitch(unsigned char _pin, ScheduleInterval &_interval, Clock &_clockSensor) : Device(_pin), interval(_interval), clockSensor(_clockSensor) {};
    
void ScheduleIntervalSwitch::update() {
  unsigned int currentTimeInPeriod = clockSensor.toEpochMinutes() % interval.period;

  isEnabled = currentTimeInPeriod < interval.enableFor;
  writeToPinInverted();
};

#include <Arduino.h>
#include "Sodaq_DS3231.h"
#include "./Clock.h"

void Clock::init() {
  rtc.begin();
};

void Clock::update() {
  dateTime = rtc.now();
}

// hours and minutes in int
unsigned int Clock::getIntTime() {
  // uncomment for debug with seconds
  // return 7 * 60 + dateTime.second();
  
  return dateTime.hour() * 60 + dateTime.minute();
}

// number of minutes since 01.01.2000 00:00
uint32_t Clock::toEpochMinutes() {
  // uncomment for debug with seconds
  // return dateTime.getEpoch();
  
  return dateTime.getEpoch() % 60;
}


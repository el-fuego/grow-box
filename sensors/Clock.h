#ifndef CLOCK_H
#define CLOCK_H

#include "Sodaq_DS3231.h"
#include "./Sensor.h"

class Clock: public Sensor {
  public:
    DateTime dateTime;
  	void init();
    void update();
    unsigned int getIntTime();
    uint32_t toEpochMinutes();
};

#endif;
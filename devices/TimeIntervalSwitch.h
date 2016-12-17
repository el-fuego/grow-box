#ifndef TIME_INTERVAL_SWITCH_H
#define TIME_INTERVAL_SWITCH_H

#include "./Device.h"
#include "../sensors/Clock.h"
#include "../settings.h"

class TimeIntervalSwitch: public Device {
  private:
    TimeInterval &interval;
    Clock &clockSensor;
  public:
    TimeIntervalSwitch(unsigned char _pin, TimeInterval &_interval, Clock &_clockSensor);
    void update();
};

#endif;
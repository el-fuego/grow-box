#ifndef SCHEDULE_INTERVAL_SWITCH_H
#define SCHEDULE_INTERVAL_SWITCH_H

#include "./Device.h"
#include "../sensors/Clock.h"
#include "../settings.h"

class ScheduleIntervalSwitch: public Device {
  private:
    ScheduleInterval &interval;
    Clock &clockSensor;
  public:
    ScheduleIntervalSwitch(unsigned char _pin, ScheduleInterval &_interval, Clock &_clockSensor);
    void update();
};

#endif;
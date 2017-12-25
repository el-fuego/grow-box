#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino-devices.h>


struct BasedOnDayTime {
  unsigned int day;
  unsigned int night;
};

struct Settings {
  unsigned int structVersion;
  BasedOnDayTime temperature;
  unsigned int humidity;
  TimeInterval lightening;
  ScheduleInterval watering;
  ScheduleInterval dwcAeration;
  unsigned int wateringSalinity;
  unsigned int dwcSalinity;
  unsigned int airCirculation;
};

#endif;

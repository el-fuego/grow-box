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
  ScheduleInterval airInflow;
};

extern Settings s1_settings;
extern Settings s2_settings;
extern Settings s3_settings;
extern const Settings defaultSettings;

#endif

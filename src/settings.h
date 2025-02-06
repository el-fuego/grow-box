#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino-progmem-menu.h>

struct BasedOnDayTime {
  unsigned int day;
  unsigned int night;
};
struct TimeInterval {
  unsigned int fromMinutes;
  unsigned int toMinutes;
};
struct ScheduleInterval {
  unsigned int enableForMinutes;
  unsigned int periodMinutes;
};

struct Settings {
  unsigned int structVersion;
  TimeInterval lightening;
  ScheduleInterval ventilation;
  unsigned int humidity;
  BasedOnDayTime temperature;
//   ScheduleInterval watering;
//   unsigned int wateringSalinity;
//   ScheduleInterval dwcAeration;
//   unsigned int dwcSalinity;
//   unsigned int airCirculation;
};

extern Settings settings;
extern const Settings defaultSettings;

#endif

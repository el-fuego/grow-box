#ifndef SETTINGS_H
#define SETTINGS_H

struct BasedOnDayTime {
  unsigned int day;
  unsigned int night;
};

struct ScheduleInterval {
  unsigned int enableFor;
  unsigned int period;
};

struct TimeInterval {
  unsigned int from;
  unsigned int to;
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

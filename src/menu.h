#ifndef MENU_STRUCT_H
#define MENU_STRUCT_H

#include <Arduino-progmem-menu.h>
#include "./settings.h"


#define MIN_TEMPERATURE 15
#define MAX_TEMPERATURE 35
#define MAX_TIME 24*60 - 1 // 11:59 PM

#define CRETE_SECTION_MENU(index) \
  MENU(s##index##_temperature, "Temperature", 0\
    ,NUMBER_FIELD(s##index##_temperatureDay,   "Day ", s##index##_settings.temperature.day, Menu::to2Digits, "C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)\
    ,NUMBER_FIELD(s##index##_temperatureNight, "Night ", s##index##_settings.temperature.night, Menu::to2Digits, "C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)\
  );\
  \
  MENU(s##index##_humidity, "Humidity", 0\
    ,NUMBER_FIELD(s##index##_humidityValue, "Value ", s##index##_settings.humidity, Menu::to2Digits, "%", 10, 90, 5)\
    ,BLANK()\
  );\
  \
  MENU(s##index##_lightening, "Lightening", 0\
    ,NUMBER_FIELD(s##index##_lighteningFrom, "From ", s##index##_settings.lightening.from, Menu::toTime24, "", 0, MAX_TIME, 10)\
    ,NUMBER_FIELD(s##index##_lighteningTo,   "To ", s##index##_settings.lightening.to, Menu::toTime24, "", 0, MAX_TIME, 10)\
  );\
  \
  MENU(s##index##_watering, "Watering", 0\
    ,NUMBER_FIELD(s##index##_wateringFor,   "For ", s##index##_settings.watering.enableFor, Menu::toPeriod, "", 0, MAX_TIME, 1)\
    ,NUMBER_FIELD(s##index##_wateringEvery, "Every ", s##index##_settings.watering.period, Menu::toPeriod, "", 0, MAX_TIME, 1)\
  );\
  \
  MENU(s##index##_dwcAeration, "Aeration", 0\
    ,NUMBER_FIELD(s##index##_dwcAerationFor,   "For ", s##index##_settings.dwcAeration.enableFor, Menu::toPeriod, " ", 0, MAX_TIME, 1)\
    ,NUMBER_FIELD(s##index##_dwcAerationEvery, "Every ", s##index##_settings.dwcAeration.period, Menu::toPeriod, "", 0, MAX_TIME, 1)\
  );\
  \
  MENU(s##index##_dwcSalinity, "DWC Salinity", 0\
    ,NUMBER_FIELD(s##index##_dwcSalinityValue, "Value ", s##index##_settings.dwcSalinity, Menu::to4Digits, "ppt", 50, 3000, 10)\
    ,BLANK()\
  );\
  \
  MENU(s##index##_wateringSalinity, "Watering Sal.", 0\
    ,NUMBER_FIELD(s##index##_wateringSalinityValue, "Value ", s##index##_settings.wateringSalinity, Menu::to4Digits, "ppt", 50, 3000, 10)\
    ,BLANK()\
  );\
  \
  MENU(s##index##_airCirculation, "Air circulat.", 0\
    ,NUMBER_FIELD(s##index##_airCirculationValue, "Value ", s##index##_settings.airCirculation, Menu::to2Digits, "%", 0, 100, 5)\
    ,BLANK()\
  );\
  \
  MENU(s##index##_airInflow, "Air inflow.", 0\
    ,NUMBER_FIELD(s##index##_airInflowFor,   "For ", s##index##_settings.airInflow.enableFor, Menu::toPeriod, "", 0, MAX_TIME, 1)\
    ,NUMBER_FIELD(s##index##_airInflowEvery, "Every ", s##index##_settings.airInflow.period, Menu::toPeriod, "", 0, MAX_TIME, 1)\
  );\
  \
  MENU(section##index, "Section " #index, 0\
    ,SUBMENU(s##index##_temperature)\
    ,SUBMENU(s##index##_humidity)\
    ,SUBMENU(s##index##_lightening)\
    ,SUBMENU(s##index##_watering)\
    ,SUBMENU(s##index##_dwcAeration)\
    ,SUBMENU(s##index##_dwcSalinity)\
    ,SUBMENU(s##index##_wateringSalinity)\
    ,SUBMENU(s##index##_airCirculation)\
    ,SUBMENU(s##index##_airInflow)\
  );\


CRETE_SECTION_MENU(1);
CRETE_SECTION_MENU(2);
CRETE_SECTION_MENU(3);


MENU(settings, "Settings", Menu::NAME_HIDDEN_FOR_CHILD_LIST
  ,SUBMENU(section1)
  ,SUBMENU(section2)
  ,SUBMENU(section3)
);

#endif

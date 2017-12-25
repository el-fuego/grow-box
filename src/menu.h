#ifndef MENU_STRUCT_H
#define MENU_STRUCT_H

#include <Arduino-progmem-menu.h>
#include "./settings.h"


#define MIN_TEMPERATURE 15
#define MAX_TEMPERATURE 35
#define MAX_TIME 24*60 - 1 // 11:59 PM


MENU(temperature, "Temperature", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(temperatureDay,   "Day", currentSettings.temperature.day, Menu::to2Digits, "C ", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)
  ,NUMBER_FIELD(temperatureNight, "Night", currentSettings.temperature.night, Menu::to2Digits, "C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)
);

MENU(humidity, "Humidity", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(humidityValue, "", currentSettings.humidity, Menu::to2Digits, "%", 10, 90, 5)
  ,BLANK()
);

MENU(lightening, "Lightening", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(lighteningFrom, "", currentSettings.lightening.from, Menu::toTime24, "-", 0, MAX_TIME, 10)
  ,NUMBER_FIELD(lighteningTo,   "", currentSettings.lightening.to, Menu::toTime24, "", 0, MAX_TIME, 10)
);

MENU(watering, "Watering", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(wateringFor,   "For", currentSettings.watering.enableFor, Menu::toPeriod, " ", 0, MAX_TIME, 1)
  ,NUMBER_FIELD(wateringEvery, "Every", currentSettings.watering.period, Menu::toPeriod, "", 0, MAX_TIME, 1)
);

MENU(dwcAeration, "Aeration", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(dwcAerationFor,   "For", currentSettings.dwcAeration.enableFor, Menu::toPeriod, " ", 0, MAX_TIME, 1)
  ,NUMBER_FIELD(dwcAerationEvery, "Every", currentSettings.dwcAeration.period, Menu::toPeriod, "", 0, MAX_TIME, 1)
);

MENU(dwcSalinity, "DWC Salinity", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(dwcSalinityValue, "", currentSettings.dwcSalinity, Menu::to4Digits, "ppt", 50, 3000, 10)
  ,BLANK()
);

MENU(wateringSalinity, "Watering Sal.", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(wateringSalinityValue, "", currentSettings.wateringSalinity, Menu::to4Digits, "ppt", 50, 3000, 10)
  ,BLANK()
);

MENU(airCirculation, "Air circulat.", Menu::HORIZONTAL_CHILD_LIST
  ,NUMBER_FIELD(airCirculationValue, "", currentSettings.airCirculation, Menu::to2Digits, "%", 0, 100, 5)
  ,BLANK()
);

//MENU(currentTime, "Current Time", Menu::HORIZONTAL_CHILD_LIST
//  ,NUMBER_FIELD(currentTimeValue, "", clock.dateTime, Menu::toTime24, "%", 10, 90, 5)
//  ,BLANK()
//);

MENU(settings, "Settings", Menu::NAME_HIDDEN_FOR_CHILD_LIST
  ,SUBMENU(temperature)
  ,SUBMENU(humidity)
  ,SUBMENU(lightening)
  ,SUBMENU(watering)
  ,SUBMENU(dwcAeration)
  ,SUBMENU(dwcSalinity)
  ,SUBMENU(wateringSalinity)
  ,SUBMENU(airCirculation)
);


#endif;

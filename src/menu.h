#ifndef MENU_STRUCT_H
#define MENU_STRUCT_H

#include <Arduino-progmem-menu.h>
#include "./settings.h"


#define MIN_TEMPERATURE 15
#define MAX_TEMPERATURE 35
#define MAX_TIME 24*60 - 1 // 11:59 PM

void setGrowSettings() {
  settings = GROW_SETTINGS;
};
void setBloomSettings() {
  settings = BLOOM_SETTINGS;
};

MENU(s_mode, "Load Presets", 0
  ,ACTION(setGrowSettingsAction, "Grow", setGrowSettings)
  ,ACTION(setBloomSettingsAction, "Bloom", setBloomSettings)
);

MENU(s_lightening, "Lightening", 0
  ,NUMBER_FIELD(s_lighteningFrom, "From ", settings.lightening.fromMinutes, Menu::toTime24, "", 0, MAX_TIME, 10)
  ,NUMBER_FIELD(s_lighteningTo,   "To ", settings.lightening.toMinutes, Menu::toTime24, "", 0, MAX_TIME, 10)
);
MENU(s_ventilation, "Ventilation", 0
  ,NUMBER_FIELD(s_ventilationFor,   "For ", settings.ventilation.enableForMinutes, Menu::toPeriod, "", 0, MAX_TIME, 1)
  ,NUMBER_FIELD(s_ventilationEvery, "Every ", settings.ventilation.periodMinutes, Menu::toPeriod, "", 0, MAX_TIME, 1)
);
MENU(s_humidity, "Humidity", 0
  ,NUMBER_FIELD(s_humidityValue, "Value ", settings.humidity, Menu::to2Digits, "%", 10, 90, 5)
  ,BLANK()
);
MENU(s_temperature, "Temperature", 0
  ,NUMBER_FIELD(s_temperatureDay,   "Day ", settings.temperature.day, Menu::to2Digits, "C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)
  ,NUMBER_FIELD(s_temperatureNight, "Night ", settings.temperature.night, Menu::to2Digits, "C", MIN_TEMPERATURE, MAX_TEMPERATURE, 1)
);
// MENU(s_watering, "Watering", 0
//   ,NUMBER_FIELD(s_wateringFor,   "For ", settings.watering.enableForMinutes, Menu::toPeriod, "", 0, MAX_TIME, 1)
//   ,NUMBER_FIELD(s_wateringEvery, "Every ", settings.watering.periodMinutes, Menu::toPeriod, "", 0, MAX_TIME, 1)
// );
// MENU(s_dwcAeration, "Aeration", 0
//   ,NUMBER_FIELD(s_dwcAerationFor,   "For ", settings.dwcAeration.enableForMinutes, Menu::toPeriod, " ", 0, MAX_TIME, 1)
//   ,NUMBER_FIELD(s_dwcAerationEvery, "Every ", settings.dwcAeration.periodMinutes, Menu::toPeriod, "", 0, MAX_TIME, 1)
// );
// MENU(s_dwcSalinity, "DWC Salinity", 0
//   ,NUMBER_FIELD(s_dwcSalinityValue, "Value ", settings.dwcSalinity, Menu::to4Digits, "ppt", 50, 3000, 10)
//   ,BLANK()
// );
// MENU(s_wateringSalinity, "Watering Sal.", 0
//   ,NUMBER_FIELD(s_wateringSalinityValue, "Value ", settings.wateringSalinity, Menu::to4Digits, "ppt", 50, 3000, 10)
//   ,BLANK()
// );
// MENU(s_airCirculation, "Air circulat.", 0
//   ,NUMBER_FIELD(s_airCirculationValue, "Value ", settings.airCirculation, Menu::to2Digits, "%", 0, 100, 5)
//   ,BLANK()
// );

MENU(settings, "Settings", Menu::NAME_HIDDEN_FOR_CHILD_LIST
  ,SUBMENU(s_mode)
  ,SUBMENU(s_lightening)
  ,SUBMENU(s_ventilation)
  ,SUBMENU(s_humidity)
  ,SUBMENU(s_temperature)
//   ,SUBMENU(s_watering)
//   ,SUBMENU(s_dwcAeration)
//   ,SUBMENU(s_dwcSalinity)
//   ,SUBMENU(s_wateringSalinity)
//   ,SUBMENU(s_airCirculation)
);

#endif

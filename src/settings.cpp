#include "./settings.h"

#define HOURS 60

const Settings defaultSettings = {
  1, // structVersion
  { 4*HOURS, 18*HOURS + 30 }, // Lightening
  { 5, 1*60 }, // Ventilation
  65, // Humidity
  { 22, 20 }, // Temperature (max): day and night
//   { 0, 1*60 }, // Watering
//   700, // Watering Salinity
//   { 0, 1*60 }, // DWC Aeration
//   700, // DWC Salinity
//   100, // Air Circulation
};

Settings settings;

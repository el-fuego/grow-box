#include "./settings.h"

#define HOURS 60

// Current RAM settings:
Settings settings;

const Settings defaultSettings = {
  // Version:
  // .. to set time. see: CURRENT_DATE, loadSettings()
  // .. or structure changes
  2,

  // Lightening, minutes:
  { 3 * HOURS + 30, 21 * HOURS + 30 },

  // Ventilation, minutes:
  {  /* for */ 2,  /* every */ 5 },

  // Humidity, %:
  65,

  // Max temperature, °C:
  { /* day */ 22,  /* night */ 20 },

//   // Watering, minutes:
//   { /* for */ 0,  /* every */ 1*60 },
//   // Watering Salinity:
//   700,
//   // DWC Aeration, minutes:
//   { /* for */ 0,  /* every */ 1*60 },
//   // DWC Salinity, minutes:
//   700,
//   // Air Circulation power, %:
//   100,
};

const Settings GROW_SETTINGS = {
  defaultSettings.structVersion,

  // Lightening, minutes:
  { 4 * HOURS, 21 * HOURS + 30 },

  // Ventilation, minutes:
  { /* for */ 2,  /* every */ 20 },

  // Humidity, %:
  65,

  // Max temperature, °C:
  { /* day */ 22,  /* night */ 20 },
};

const Settings BLOOM_SETTINGS = {
  defaultSettings.structVersion,

  // Lightening, minutes:
  { 8 * HOURS, 20 * HOURS },

  // Ventilation, minutes:
  { /* for */ 10,  /* every */ 30 },

  // Humidity, %:
  55,

  // Max temperature, °C:
  { /* day */ 25,  /* night */ 23 },
};

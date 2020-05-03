#include "./settings.h"

const Settings defaultSettings = {
  3, // structVersion
  { 22, 25 }, // temperature
  65, // humidity
  { 4*60, 20*60+30 }, // lightening
  { 0, 1*60 }, // watering
  { 0, 1*60 }, // dwcAeration
  700, // wateringSalinity
  700, // dwcSalinity
  100, // airCirculation
  { 5, 1*60 } // airInflow
};

Settings s1_settings;
Settings s2_settings;
Settings s3_settings;
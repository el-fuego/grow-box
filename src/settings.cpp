#include "./settings.h"


//2+4+2+4+4+4+2+2+2 = 26*2 = 52 bytes
const Settings defaultSettings = {
  2,
  { 20, 23 },
  55,
  { 5*60, 21*60 },
  { 0, 1*60 },
  { 0, 1*60 },
  700,
  700,
  0
};
Settings currentSettings;
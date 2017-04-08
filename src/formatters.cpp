#include <WString.h>
#include "Sodaq_DS3231.h"

String toStr(unsigned int value, unsigned char charsCount) {
  String res = String(value);

  while (res.length() < charsCount) {
    res = '0' + res;
  };
  
  return res;
};

String to2Chars(unsigned int value) {
  return toStr(value, 2);
};

String to4Chars(unsigned int value) {
  return toStr(value, 4);
};

String toTime(unsigned int value) {
  unsigned char hours = value / 60;
  unsigned char minutes = value % 60;
  return to2Chars(hours) + ":" + to2Chars(minutes);
};

String toPeriod(unsigned int value) {
  return value < 60 ? to2Chars(value) + "m" : to2Chars(value / 60) + "h";
};




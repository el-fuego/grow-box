#ifndef MENU_PARAMETER_H
#define MENU_PARAMETER_H

#include <Arduino.h>
#include "./BaseEntry.h"


class MenuParameter : public BaseEntry {
  public:
    MenuParameter(String _textBefore, unsigned int &_value, String (&_valueFormatter)(unsigned int _value), String _textAfter);
    String textBefore;
    unsigned int &value;
    String (&valueFormatter)(unsigned int value);
    String textAfter;
};

#endif;

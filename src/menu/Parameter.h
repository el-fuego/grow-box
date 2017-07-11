#ifndef PARAMETER_H
#define PARAMETER_H

#include <Arduino.h>


class Parameter {
  public:
    Parameter(String _textBefore, unsigned int &_value, String (&_valueFormatter)(unsigned int _value), String _textAfter);
    String textBefore;
    unsigned int &value;
    String (&valueFormatter)(unsigned int value);
    String textAfter;
};

#endif;

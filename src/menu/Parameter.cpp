#include "./Parameter.h"


Parameter::Parameter(String _textBefore, unsigned int &_value, String (&_valueFormatter)(unsigned int _value), String _textAfter) : textBefore(_textBefore), value(_value), valueFormatter(_valueFormatter), textAfter(_textAfter) {};

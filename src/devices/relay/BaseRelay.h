#ifndef BASE_RELAY_H
#define BASE_RELAY_H

#include "../Device.h"

class BaseRelay : public Device {
  protected:
  	unsigned long toggledAt = 0;
  	unsigned long minMeasureInterval = 10000;
  	void writeToPin();
  	bool canMeasure();
  public:
    unsigned char minDifference = 5;
    unsigned int &demandedValue;
    unsigned char &currentValue;
    BaseRelay(unsigned char _pin, unsigned int &_demandedValue, unsigned char &_currentValue);
    virtual void update();
};

#endif;
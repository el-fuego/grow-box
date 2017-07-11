#ifndef INTENSITY_CONTROL_H
#define INTENSITY_CONTROL_H

#include "./Device.h"

class IntensityControl: public Device {
  private:
    unsigned int &percentage;
    unsigned int previousPercentage = 0;
    unsigned int rangeStart = 0;
  public:
    IntensityControl(unsigned char _pin, unsigned int &_percentage);
    IntensityControl(unsigned char _pin, unsigned int &_percentage, unsigned int _rangeStart);
    unsigned int getPinValue();
    void update();
};

#endif;
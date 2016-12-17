#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#include "./Device.h"

class Humidifier: public Device {
  private:
    unsigned char minDifference = 3;
    unsigned int &demandedHumidity;
    unsigned char &currentHumidity;
  public:
    Humidifier(unsigned char _pin, unsigned int &_demandedHumidity, unsigned char &_currentHumidity);
    void update();
};

#endif;
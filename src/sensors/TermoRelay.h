#ifndef TERMO_RELAY_H
#define TERMO_RELAY_H

#include "./Sensor.h"

class TermoRelay: public Sensor {
  private:
    unsigned char pin;
    unsigned char limitValue = 500;
  public:
    TermoRelay(unsigned char _pin, unsigned char _limitValue);
    bool isEnabled = false;
  	void init();
    void update();
};

#endif;
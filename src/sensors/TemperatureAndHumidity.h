#ifndef TEMPERATURE_AND_HUMIDITY_H
#define TEMPERATURE_AND_HUMIDITY_H

#include <SimpleDHT.h>
#include "./Sensor.h"

class TemperatureAndHumidity: public Sensor {
  private:
    SimpleDHT11 driver;
    unsigned long updatedAt = 0;
    unsigned char pin;
  public:
    TemperatureAndHumidity(unsigned char _pin);
    unsigned char humidity;
    unsigned char temperature;
  	void init();
    void update();
};

#endif;
#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    bool hasError = false;
  	virtual void init();
    virtual void update();
};

#endif;
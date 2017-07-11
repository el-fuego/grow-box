#ifndef JOISTIC_H
#define JOISTIC_H
#include "./Sensor.h"


enum Directions { Center, Up, Down, Left, Right };

class Joystick: public Sensor {
  private:
    unsigned char pinX;
    unsigned char pinY;
    Directions read();
    Directions prevDirection = Center;
    unsigned long updatedAt;
  public:
    Joystick(unsigned char _pinX, unsigned char _pinY);
    Directions direction = Center;
  	void init();
    void update();
};

#endif


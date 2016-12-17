#include <Arduino.h>
#include "./Joystick.h"

Joystick::Joystick(unsigned char _pinX, unsigned char _pinY) : pinX(_pinX), pinY(_pinY) {};
    
void Joystick::init() {
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
};

void Joystick::update() {
  Directions currentDirection = read();
  
  // single press
  if (currentDirection != prevDirection) {
    direction = currentDirection;
    directionWasSetAt = millis();
  // long press
  } else if (millis() - directionWasSetAt > 500) {
      direction = currentDirection;
  } else {
      direction = Center;
  }

  prevDirection = currentDirection;
};

Directions Joystick::read() {
  int valueX = analogRead(pinX);
  if (valueX > 923) {
    return Right;
  }
  if (valueX < 100) {
    return Left;
  }
  
  int valueY = analogRead(pinY);
  if (valueY > 923) {
    return Down;
  }
  if (valueY < 100) {
    return Up;
  }
  return Center;
};


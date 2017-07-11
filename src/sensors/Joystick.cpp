#include <Arduino.h>
#include "./Joystick.h"

#define LONG_PRESS_TIMEOUT 500


Joystick::Joystick(unsigned char _pinX, unsigned char _pinY) : pinX(_pinX), pinY(_pinY) {};
    
void Joystick::init() {
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
};

void Joystick::update() {
  Directions currentDirection = read();
  unsigned long currentTime = millis();
  if (updatedAt > currentTime) {
    updatedAt = 0;
  }
  
  // single press
  if (currentDirection != prevDirection) {
    direction = prevDirection = currentDirection;
    updatedAt = currentTime;

  // long press
  } else if (currentTime - updatedAt > LONG_PRESS_TIMEOUT) {
      direction = currentDirection;

  } else {
      direction = Center;
  }
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


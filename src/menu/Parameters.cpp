#include <Arduino-devices.h>
#include "./Parameters.h"


void Parameters::add(Parameter* item) {
  items[itemsCount] = item;
  itemsCount++;
};

Parameter* Parameters::get(unsigned char index) {
  return items[index];
};

void Parameters::selectPrev() {
  selectedIndex--;
};

void Parameters::selectNext() {
  if (selectedIndex < itemsCount - 1) {
    selectedIndex++;
  }
};

void Parameters::increaseValue() {
  items[selectedIndex]->value++;
};

void Parameters::decreaseValue() {
  if (items[selectedIndex]->value > 0) {
    items[selectedIndex]->value--;
  }
};

void Parameters::navigate(unsigned char button) {
  switch(button) {  
    case JoystickDirections::Up:
      increaseValue();
      break;
    case JoystickDirections::Down:
      decreaseValue();
      break;
    case JoystickDirections::Left:
      if (selectedIndex == 0) {
        this->exit();
      } else {
        selectPrev();
      }
      break;
    case JoystickDirections::Right:
      selectNext();
      break;
  }
};



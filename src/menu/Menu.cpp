#include <Arduino-devices.h>
#include "./Menu.h"


void Menu::add(MenuItem* item) {
  items[itemsCount] = item;
  itemsCount++;
};

MenuItem* Menu::get(unsigned char index) {
  return items[index];
};

void Menu::selectPrev() {
  if (selectedIndex == 0) {
    selectedIndex = itemsCount - 1;
  } else {
    selectedIndex--;
  }
};

void Menu::selectNext() {
  selectedIndex++;
  if (selectedIndex >= itemsCount) {
    selectedIndex = 0;
  }
};

bool Menu::isParamsActive() {
  return isActive && items[selectedIndex]->parameters->isActive;
};

void Menu::navigate(unsigned char button) {
  if (isActive) {
    if (isParamsActive()) {
      items[selectedIndex]->parameters->navigate(button);
    } else {
      switch(button) {
        case JoystickDirections::Up:
          selectPrev();
          break;
        case JoystickDirections::Down:
          selectNext();
          break;
        case JoystickDirections::Left:
          this->exit();
          break;
        case JoystickDirections::Right:
          items[selectedIndex]->parameters->enter();
          break;
      }
    }
  } else if (button != JoystickDirections::Center) {
    this->enter();
  }
};

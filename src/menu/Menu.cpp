#include "./Menu.h"
#include "../sensors/Joystick.h"


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
        case Up:
          selectPrev();
          break;
        case Down:
          selectNext();
          break;
        case Left:
          this->exit();
          break;
        case Right:
          items[selectedIndex]->parameters->enter();
          break;
      }
    }
  } else if (button != Center) {
    this->enter();
  }
};

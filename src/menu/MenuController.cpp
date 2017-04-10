#include "./MenuController.h"
#include "../sensors/Joystick.h"


void MenuController::add(Menu *item) {
  items[itemsCount] = item;
  itemsCount++;
};

void MenuController::selectPrev() {
  if (selectedIndex == 0) {
    selectedIndex = itemsCount - 1;
  } else {
    selectedIndex--;
  }
};

void MenuController::selectNext() {
  selectedIndex++;
  if (selectedIndex >= itemsCount) {
    selectedIndex = 0;
  }
};

bool MenuController::hasActiveController() {
  return isActive && items[selectedIndex]->controller->isActive;
};

void MenuController::navigate(unsigned char button) {
  if (isActive) {
    if (hasActiveController()) {
      items[selectedIndex]->controller->navigate(button);
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
          items[selectedIndex]->controller->enter();
          break;
      }
    }
  } else if (button != Center) {
    this->enter();
  }
};

#include "./MenuParameterController.h"
#include "../sensors/Joystick.h"


void MenuParameterController::add(MenuParameter *item) {
  items[itemsCount] = item;
  itemsCount++;
};

void MenuParameterController::selectPrev() {
  selectedIndex--;
};

void MenuParameterController::selectNext() {
  if (selectedIndex < itemsCount - 1) {
    selectedIndex++;
  }
};

void MenuParameterController::increaseValue() {
  items[selectedIndex]->value++;
};

void MenuParameterController::decreaseValue() {
  if (items[selectedIndex]->value > 0) {
    items[selectedIndex]->value--;
  }
};

void MenuParameterController::navigate(unsigned char button) {
  switch(button) {  
    case Up:
      increaseValue();
      break;
    case Down:
      decreaseValue();
      break;
    case Left:
      if (selectedIndex == 0) {
        this->exit();
      } else {
        selectPrev();
      }
      break;
    case Right:
      selectNext();
      break;
  }
};



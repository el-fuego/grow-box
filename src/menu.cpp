#include "./menu.h"
#include "./sensors/Joystick.h"


MenuParameter::MenuParameter(String _textBefore, unsigned int &_value, String (&_valueFormatter)(unsigned int _value), String _textAfter) : textBefore(_textBefore), value(_value), valueFormatter(_valueFormatter), textAfter(_textAfter) {};


MenuEntriesController::MenuEntriesController() {};
MenuEntriesController::MenuEntriesController(void (&_onEnter)()) : onEnter(_onEnter) {};
MenuEntriesController::MenuEntriesController(void (&_onEnter)(), void (&_onExit)()) : onEnter(_onEnter), onExit(_onExit) {};

void MenuEntriesController::add(MenuEntry *item) {
  items[itemsCount] = item;
  itemsCount++;
};

void MenuEntriesController::exit() {
  isActive = false;
  onExit();
};

void MenuEntriesController::enter() {
  isActive = true;
  selectedIndex = 0;
  onEnter();
};

bool MenuEntriesController::hasActiveController() {
  return false;
};


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



Menu::Menu(String _name, MenuEntriesController *_controller) : name(_name), controller(_controller) {};

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

#include "./BaseController.h"


BaseController::BaseController() {};
BaseController::BaseController(void (&_onEnter)()) : onEnter(_onEnter) {};
BaseController::BaseController(void (&_onEnter)(), void (&_onExit)()) : onEnter(_onEnter), onExit(_onExit) {};

void BaseController::add(BaseEntry *item) {
  items[itemsCount] = item;
  itemsCount++;
};

void BaseController::exit() {
  isActive = false;
  onExit();
};

void BaseController::enter() {
  isActive = true;
  selectedIndex = 0;
  onEnter();
};

bool BaseController::hasActiveController() {
  return false;
};


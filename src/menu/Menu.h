#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "./BaseEntry.h"
#include "./BaseController.h"


class Menu : public BaseEntry {
  public:
    Menu(String _name, BaseController *_controller);
    String name;
    BaseController *controller;
};

#endif;

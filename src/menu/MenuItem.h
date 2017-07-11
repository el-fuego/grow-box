#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>
#include "./Parameters.h"


class MenuItem {
  public:
    MenuItem(String _name, Parameters* _parameterController);
    String name;
    Parameters* parameters;
};

#endif;

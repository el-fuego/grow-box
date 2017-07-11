#ifndef MENU_H
#define MENU_H

#include "./BaseController.h"
#include "./MenuItem.h"


class Menu : public BaseController {
  private:
    void selectPrev();
    void selectNext();
    MenuItem* items[8];
  public:
    using BaseController::BaseController;
    void add(MenuItem* item);
    MenuItem* get(unsigned char index);
    bool isParamsActive();
    void navigate(unsigned char button);
};

#endif;

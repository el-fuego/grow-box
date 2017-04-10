#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "./BaseController.h"
#include "./Menu.h"


class MenuController : public BaseController {
  private:
    void selectPrev();
    void selectNext();
  public:
    using BaseController::BaseController;
    Menu *items[8];
    void add(Menu *item);
    bool hasActiveController();
    void navigate(unsigned char button);
};

#endif;

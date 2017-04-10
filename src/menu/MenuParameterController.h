#ifndef MENU_PARAMETER_CONTROLLER_H
#define MENU_PARAMETER_CONTROLLER_H

#include "./BaseController.h"
#include "./MenuParameter.h"


class MenuParameterController : public BaseController {
  private:
    void selectPrev();
    void selectNext();
    void increaseValue();
    void decreaseValue();
  public:
    using BaseController::BaseController;
    MenuParameter *items[8];
    void add(MenuParameter *item);
    void navigate(unsigned char button);
};

#endif;

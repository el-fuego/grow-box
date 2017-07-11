#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "./BaseController.h"
#include "./Parameter.h"


class Parameters : public BaseController {
  private:
    void selectPrev();
    void selectNext();
    void increaseValue();
    void decreaseValue();
    Parameter* items[4];
  public:
    using BaseController::BaseController;
    Parameter* get(unsigned char index);
    void add(Parameter* item);
    void navigate(unsigned char button);
};

#endif;

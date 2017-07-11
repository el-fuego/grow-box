#ifndef TURN_ON_WHEN_HIGHER_H
#define TURN_ON_WHEN_HIGHER_H

#include "./BaseRelay.h"

class TurnOnWhenHigher : public BaseRelay {
  public:
    using BaseRelay::BaseRelay;
    void update();
};

#endif;
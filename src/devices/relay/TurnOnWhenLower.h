#ifndef TURN_ON_WHEN_LOWER_H
#define TURN_ON_WHEN_LOWER_H

#include "./BaseRelay.h"

class TurnOnWhenLower : public BaseRelay {
  public:
    using BaseRelay::BaseRelay;
    void update();
};

#endif;
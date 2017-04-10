#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include "./BaseEntry.h"


class BaseController {
  public:
    BaseController();
    BaseController(void (&_onEnter)());
    BaseController(void (&_onEnter)(), void (&_onExit)());
    BaseEntry *items[8];
    unsigned char itemsCount = 0;
    unsigned char selectedIndex = 0;
    bool isActive = false;
    void (&onEnter)();
    void (&onExit)();
    void add(BaseEntry *item);
    void enter();
    void exit();
    bool hasActiveController();
    virtual void navigate(unsigned char button);
};


#endif;

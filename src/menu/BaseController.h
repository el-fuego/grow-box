#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

class BaseController {
  public:
    BaseController();
    BaseController(void (&_onEnter)());
    BaseController(void (&_onEnter)(), void (&_onExit)());
    unsigned char itemsCount = 0;
    unsigned char selectedIndex = 0;
    bool isActive = false;
    void (&onEnter)();
    void (&onExit)();
    void enter();
    void exit();
    virtual void navigate(unsigned char button);
};


#endif;

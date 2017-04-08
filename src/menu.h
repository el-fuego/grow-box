#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

class MenuEntry {};

class MenuEntriesController {
  public:
    MenuEntriesController();
    MenuEntriesController(void (&_onEnter)());
    MenuEntriesController(void (&_onEnter)(), void (&_onExit)());
    MenuEntry *items[8];
    unsigned char itemsCount = 0;
    unsigned char selectedIndex = 0;
    bool isActive = false;
    void (&onEnter)();
    void (&onExit)();
    void add(MenuEntry *item);
    void enter();
    void exit();
    bool hasActiveController();
    virtual void navigate(unsigned char button);
};


class MenuParameter : public MenuEntry {
  public:
    MenuParameter(String _textBefore, unsigned int &_value, String (&_valueFormatter)(unsigned int _value), String _textAfter);
    String textBefore;
    unsigned int &value;
    String (&valueFormatter)(unsigned int value);
    String textAfter;
};

class MenuParameterController : public MenuEntriesController {
  private:
    void selectPrev();
    void selectNext();
    void increaseValue();
    void decreaseValue();
  public:
    using MenuEntriesController::MenuEntriesController;
    MenuParameter *items[8];
    void add(MenuParameter *item);
    void navigate(unsigned char button);
};



class Menu : public MenuEntry {
  public:
    Menu(String _name, MenuEntriesController *_controller);
    String name;
    MenuEntriesController *controller;
};

class MenuController : public MenuEntriesController {
  private:
    void selectPrev();
    void selectNext();
  public:
    using MenuEntriesController::MenuEntriesController;
    Menu *items[8];
    void add(Menu *item);
    bool hasActiveController();
    void navigate(unsigned char button);
};

#endif;

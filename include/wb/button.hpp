#pragma once

#include <EasyButton.h>
#include <functional>
#include <xtensa/config/specreg.h>

#include "wb/definitions.hpp"

class wbButton {
public:
  wbButton(int delay, int pin, int debounceTime, int pullup, int alow)
      : holdDelay(delay), button(pin, debounceTime, pullup, alow) {}

  void init();
  bool read();

  bool clicked();
  bool held();

private:
  int holdDelay;
  EasyButton button;
  bool wasClicked;
  bool wasHeld;

  void buttonISR();
  void holdCallback();
  void clickCallback();

  unsigned long lastPressed;
};

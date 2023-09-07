#pragma once

#include <EasyButton.h>
#include <functional>
#include <xtensa/config/specreg.h>

#include "wb/definitions.hpp"

class wbButton {
public:
  wbButton(int delay, int pin, int debounceTime, bool pullup, bool alow);

  void init();
  auto read() -> bool;
  auto clicked() -> bool;
  auto held() -> bool;

private:
  int holdDelay;
  EasyButton button;
  bool wasClicked;
  bool wasHeld;

  void buttonISR();
  void holdCallback();
  void clickCallback();

  unsigned long lastPressed{};
};

#pragma once

// FIXME: pile of headers
#include <esp32-hal-gpio.h>
#include <esp32-hal.h>
#include <esp_attr.h>
#include <functional>
#include <sys/_types.h>
#include <xtensa/config/specreg.h>

#include "wb/definitions.hpp"

enum buttonState {
  BUTTON_RELEASED,
  BUTTON_CLICKED,
  BUTTON_DOUBLE_CLICKED,
  BUTTON_TRIPLE_CLICKED,
  BUTTON_HELD
};

class wbButton {
public:
  wbButton(unsigned int pin, unsigned int holdDelay, unsigned int clickDelay,
           unsigned int debounceInterval)
      : pin(pin), holdDelay(holdDelay), clickDelay(clickDelay),
        debounceInterval(debounceInterval){};

  void init();
  auto read() -> bool;
  auto clicked() -> bool;
  auto doubleClicked() -> bool;
  auto tripleClicked() -> bool;
  auto held() -> bool;

private:
  unsigned int pin;
  unsigned int holdDelay;  // delay between press and release enough to set
                           // wasHeld to true
  unsigned int clickDelay; // delay between clicks to double and triple click
  unsigned int debounceInterval;
  unsigned int lastReleased{0};
  unsigned int lastPressed{0};
  enum buttonState state { buttonState::BUTTON_RELEASED };

  static void buttonISR(void *);
  static void updateState(wbButton *, unsigned int &&, unsigned int &&);
  auto isReleased() const -> bool;
  auto isPressed() const -> bool;
  void reset();
};

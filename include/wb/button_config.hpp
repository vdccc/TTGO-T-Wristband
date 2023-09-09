#pragma once

#include "types.hpp"

class ButtonConfig {
public:
  ButtonConfig(u8 pin, u8 pwrPin, u32 debounceInterval, u32 holdDelay,
               u32 clickDelay)
      : pin(pin), pwrPin(pwrPin), debounceInterval(debounceInterval),
        holdDelay(holdDelay), clickDelay(clickDelay) {}

  u8 pin;
  u8 pwrPin;
  u32 debounceInterval;
  u32 holdDelay;
  u32 clickDelay;
};

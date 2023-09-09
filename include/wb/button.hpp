#pragma once

#include <esp32-hal-gpio.h>
#include <functional>

#include "types.hpp"
#include "wb/button_config.hpp"
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
  wbButton(ButtonConfig config) : config(config){};

  void init();
  auto clicked() -> bool;
  auto doubleClicked() -> bool;
  auto tripleClicked() -> bool;
  auto held() -> bool;
  auto ready() const -> bool;

private:
  ButtonConfig config;

  u32 lastReleased{0}; // correct, debounced, logical
  u32 lastPressed{0};
  u32 dblastReleased{0}; // used only for debouncing
  u32 dblastPressed{0};
  enum buttonState state { buttonState::BUTTON_RELEASED };

  static void buttonISR(void *);
  static void updateState(wbButton *, u32 const &, u32 const &);
  static auto debounced(wbButton *, u32 const &&) -> bool;
  auto isReleased() const -> bool;
  auto isPressed() const -> bool;
  void clearState();
};

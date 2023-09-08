#include "wb/button.hpp"
#include "esp32-hal-gpio.h"

// FIXME: avoid usag of defines
void wbButton::init() {
  pinMode(TP_PWR_PIN, PULLUP);
  digitalWrite(TP_PWR_PIN, HIGH);
  attachInterruptArg(pin, buttonISR, this, CHANGE);
}

auto wbButton::isPressed() const -> bool { return digitalRead(pin) == HIGH; }

auto wbButton::isReleased() const -> bool { return digitalRead(pin) == LOW; }

void wbButton::updateState(wbButton *button, unsigned int &&heldFor,
                           unsigned int &&releasedFor) {
  if (heldFor > button->holdDelay) {
    button->state = buttonState::BUTTON_HELD;
    return;
  }
  if (button->state == buttonState::BUTTON_DOUBLE_CLICKED &&
      releasedFor > button->clickDelay) {
    button->state = buttonState::BUTTON_TRIPLE_CLICKED;
    return;
  }
  if (button->state == buttonState::BUTTON_CLICKED &&
      releasedFor > button->clickDelay) {
    button->state = buttonState::BUTTON_DOUBLE_CLICKED;
    return;
  }
  button->state = buttonState::BUTTON_CLICKED;
}

void wbButton::buttonISR(void *buttonPtr) {
  auto *button = static_cast<wbButton *>(buttonPtr);
  const auto curTime = millis();
  const auto heldFor = curTime - button->lastPressed;
  const auto releasedFor = curTime - button->lastReleased;
  const auto debounced = (heldFor > button->debounceInterval) &&
                         (releasedFor > button->debounceInterval);
  if (button->isPressed()) {
    button->lastPressed = curTime;
  }
  if (button->isReleased()) {
    button->lastReleased = curTime;
  }
  if (!debounced) {
    return;
  }
  if (button->isReleased()) {
    button->updateState(button, heldFor, releasedFor);
  } 
}

void wbButton::reset() {
  state = buttonState::BUTTON_RELEASED;
}

auto wbButton::clicked() -> bool {
  const auto res = state == buttonState::BUTTON_CLICKED;
  reset();
  return res;
}

auto wbButton::doubleClicked() -> bool {
  const auto res = state == buttonState::BUTTON_DOUBLE_CLICKED;
  reset();
  return res;
}

auto wbButton::tripleClicked() -> bool {
  const auto res = state == buttonState::BUTTON_TRIPLE_CLICKED;
  reset();
  return res;
}

auto wbButton::held() -> bool { 
  const auto res = state == buttonState::BUTTON_HELD;
  reset();
  return res;
}

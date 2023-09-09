#include "wb/button.hpp"

void wbButton::init() {
  pinMode(config.pwrPin, PULLUP);
  digitalWrite(config.pwrPin, HIGH);
  attachInterruptArg(config.pin, buttonISR, this, CHANGE);
}

auto wbButton::isPressed() const -> bool {
  return digitalRead(config.pin) == HIGH;
}

auto wbButton::isReleased() const -> bool {
  return digitalRead(config.pin) == LOW;
}

void wbButton::updateState(wbButton *button, u32 const &heldFor,
                           u32 const &releasedFor) {
  if (heldFor > button->config.holdDelay) {
    button->state = buttonState::BUTTON_HELD;
  } else if (releasedFor < button->config.clickDelay &&
             heldFor < button->config.holdDelay &&
             button->state == buttonState::BUTTON_DOUBLE_CLICKED) {
    button->state = buttonState::BUTTON_TRIPLE_CLICKED;
  } else if (releasedFor < button->config.clickDelay &&
             heldFor < button->config.holdDelay &&
             button->state == buttonState::BUTTON_CLICKED) {
    button->state = buttonState::BUTTON_DOUBLE_CLICKED;
  } else if (heldFor < button->config.holdDelay &&
             button->state == buttonState::BUTTON_RELEASED) {
    button->state = buttonState::BUTTON_CLICKED;
  }
}

auto wbButton::debounced(wbButton *button, u32 const &&curTime) -> bool {
  if (button->isReleased()) {
    const auto heldFor = curTime - button->dblastPressed;
    button->dblastReleased = curTime;
    return heldFor > button->config.debounceInterval;
  }
  const auto releasedFor = curTime - button->dblastReleased;
  button->dblastPressed = curTime;
  return releasedFor > button->config.debounceInterval;
}

void wbButton::buttonISR(void *buttonPtr) {
  auto *button = static_cast<wbButton *>(buttonPtr);
  const auto curTime = millis();
  if (!debounced(button, curTime)) {
    return;
  }
  if (button->isReleased()) {
    const auto heldFor = curTime - button->lastPressed;
    const auto releasedFor = button->lastPressed - button->lastReleased;
    button->lastReleased = curTime;
    button->updateState(button, heldFor,
                        releasedFor); // update state only on falling edge
  } else {
    button->lastPressed = curTime;
  }
}

auto wbButton::ready() const -> bool {
  const auto curTime = millis();
  return (curTime - lastReleased > config.clickDelay) && isReleased();
}

void wbButton::clearState() { state = buttonState::BUTTON_RELEASED; }

auto wbButton::clicked() -> bool {
  const auto res = state == buttonState::BUTTON_CLICKED;
  if (res) {
    clearState();
  }
  return res;
}

auto wbButton::doubleClicked() -> bool {
  const auto res = state == buttonState::BUTTON_DOUBLE_CLICKED;
  if (res) {
    clearState();
  }
  return res;
}

auto wbButton::tripleClicked() -> bool {
  const auto res = state == buttonState::BUTTON_TRIPLE_CLICKED;
  if (res) {
    clearState();
  }
  return res;
}

auto wbButton::held() -> bool {
  const auto res = state == buttonState::BUTTON_HELD;
  if (res) {
    clearState();
  }
  return res;
}

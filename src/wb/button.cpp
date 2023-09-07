#include "wb/button.hpp"

wbButton::wbButton(int delay, int pin, int debounceTime, bool pullup, bool alow)
    : holdDelay(delay), button(pin, debounceTime, pullup, alow),
      wasClicked(false), wasHeld(false) {
  if (button.isPressed()) {
    lastPressed = millis();
  }
}

void wbButton::init() {
  pinMode(TP_PWR_PIN, PULLUP);
  digitalWrite(TP_PWR_PIN, HIGH);
  button.begin();
  button.enableInterrupt(std::bind(&wbButton::buttonISR, this));
}

void IRAM_ATTR ARDUINO_ISR_ATTR wbButton::buttonISR() {
  const unsigned int cur = millis();
  button.read();
  wasClicked = button.wasReleased();
  wasHeld = button.wasReleased() && ((cur - lastPressed) > holdDelay);
  wasClicked = wasHeld ? false : wasClicked;
  if (button.wasPressed()) {
    lastPressed = cur;
  }
}

auto wbButton::clicked() -> bool {
  const bool status = wasClicked;
  wasClicked = false;
  return status;
}

auto wbButton::held() -> bool {
  const bool status = wasHeld;
  wasHeld = false;
  return status;
}

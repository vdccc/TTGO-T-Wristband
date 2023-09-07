#include "wb/button.hpp"

void wbButton::init() {
  pinMode(TP_PWR_PIN, PULLUP);
  digitalWrite(TP_PWR_PIN, HIGH);
  button.begin();
  button.enableInterrupt(std::bind(&wbButton::buttonISR, this));
}

void IRAM_ATTR ARDUINO_ISR_ATTR wbButton::buttonISR() {
  const unsigned int cur = millis();
  button.read();
  wasClicked = button.isReleased();
  wasHeld = button.isReleased() && ((cur - lastPressed) > holdDelay);
  wasClicked = wasHeld ? false : wasClicked;
  if (button.isPressed()) {
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

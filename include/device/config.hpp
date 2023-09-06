#pragma once

#include "wb/definitions.hpp"

class DeviceConfig {
public:
  bool serialEnabled = false;
  int buttonHoldTime = 1000;
  int buttonPin = TP_PIN_PIN;
  int buttonDebounceTime = 80;
  bool buttonPullup = true;
  bool buttonALow = false;
};

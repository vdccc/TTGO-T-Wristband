#pragma once

#include <Arduino.h>
#include <esp32-hal-gpio.h>
#include <esp_adc_cal.h>

#include "wb/definitions.hpp"

class wbBattery {
public:
  wbBattery() : vref(BATTERY_DEFAULT_VREF) {}

  void init();
  auto getVoltage() -> float;
  auto getPercent() -> int;
  static auto isCharging() -> bool;

private:
  unsigned int vref;

  static auto clamp(const int &&, const int &&, const int &&) -> int;
};

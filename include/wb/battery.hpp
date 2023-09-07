#pragma once

#include <Arduino.h>
#include <esp32-hal-gpio.h>
#include <esp_adc_cal.h>

#include "wb/definitions.hpp"

class wbBattery {
public:
  void init();
  auto getVoltage() const -> float;
  auto getPercent() const -> int;
  static auto isCharging() -> bool;

private:
  unsigned int vref{BATTERY_DEFAULT_VREF};

  static auto clamp(const int &&, const int &&, const int &&) -> int;
};

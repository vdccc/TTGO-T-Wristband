#pragma once

#include <esp32-hal-adc.h>

#include "battery_config.hpp"

class wbBattery {
public:
  wbBattery(BatteryConfig config) : config(config) {}

  void init() const;
  auto getVoltage() const -> float;
  auto getPercent() const -> u8;
  auto isCharging() const -> bool;

private:
  static auto clamp(const int &&, const int &&, const int &&) -> int;

  BatteryConfig config;
};

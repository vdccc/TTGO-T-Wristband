#pragma once

#include <Arduino.h>

#include "wb/definitions.hpp"

class wbBattery {
public:
  static void init();
  static auto getVoltage() -> float;
  static auto getPercent() -> int;
  static auto isCharging() -> bool;

private:
  static auto clamp(const int &&, const int &&, const int &&) -> int;
};

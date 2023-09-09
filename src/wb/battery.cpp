#include "wb/battery.hpp"
#include "wb/definitions.hpp"

// FIXME: make it less "static"

void wbBattery::init() {
  pinMode(CHARGE_PIN, INPUT_PULLUP);
  pinMode(BATT_ADC_PIN, INPUT);
  analogSetPinAttenuation(BATT_ADC_PIN, ADC_11db);
}

auto wbBattery::getVoltage() -> float {
  const auto val = analogRead(BATT_ADC_PIN);
  return (static_cast<float>(val) / BATTERY_ADC_MAX_RANGE) *
         BATTERY_ADC_MAX_VOLTAGE * BATTERY_VOLTAGE_DIVIDER_COEF;
}

auto wbBattery::clamp(const int &&val, const int &&low, const int &&high)
    -> int {
  if (val > high) {
    return high;
  }
  if (val < low) {
    return low;
  }
  return val;
}

auto wbBattery::getPercent() -> int {
  const float volts = getVoltage();
  float const percentage =
      ((volts - BATTERY_MIN_V) / BATTERY_RANGE) * BATTERY_MAX_PERCENT;
  return clamp((int)percentage, BATTERY_MIN_PERCENT, BATTERY_MAX_PERCENT);
}

auto wbBattery::isCharging() -> bool { return digitalRead(CHARGE_PIN) == LOW; }

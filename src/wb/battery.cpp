#include "wb/battery.hpp"
#include "wb/battery_config.hpp"

void wbBattery::init() const {
  pinMode(config.chrgPin, static_cast<u8>(config.chrgPinPullup));
  pinMode(config.adcPin, INPUT);
  analogSetPinAttenuation(config.adcPin, config.adcAtt);
}

auto wbBattery::getVoltage() const -> float {
  const auto val = analogRead(config.adcPin);
  return (static_cast<float>(val) / config.adcMaxRes) * config.adcMaxV *
         config.adcVDivCoef;
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

auto wbBattery::getPercent() const -> u8 {
  const auto volts = getVoltage();
  const auto batRange = config.batMaxV - config.batMinV;
  float const percentage = ((volts - config.batMinV) / batRange) * BAT_MAX_PCT;
  return clamp(static_cast<int>(percentage), BAT_MIN_PCT, BAT_MAX_PCT);
}

auto wbBattery::isCharging() const -> bool {
  return digitalRead(config.chrgPin) == LOW;
}

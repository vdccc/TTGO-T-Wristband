#include "wb/battery.hpp"

void wbBattery::init() {
  esp_adc_cal_characteristics_t adc_chars;
  const esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
      (adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC1_CHANNEL_6,
      (adc_bits_width_t)ADC_WIDTH_BIT_12, vref, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    vref = adc_chars.vref;
  }
  pinMode(CHARGE_PIN, INPUT_PULLUP);
}

auto wbBattery::getVoltage() -> float {
  const uint16_t val = analogRead(BATT_ADC_PIN);
  return ((float)val / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
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
  float percentage =
      ((volts - BATTERY_MIN_V) * BATTERY_MAX_PERCENT) / BATTERY_RANGE;
  return clamp((int)percentage, BATTERY_MIN_PERCENT, BATTERY_MAX_PERCENT);
}

auto wbBattery::isCharging() -> bool { return digitalRead(CHARGE_PIN) == LOW; }

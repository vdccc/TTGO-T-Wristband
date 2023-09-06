#include "wb/battery.hpp"

void wbBattery::init() {
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
      (adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC1_CHANNEL_6,
      (adc_bits_width_t)ADC_WIDTH_BIT_12, initVref, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    vref = adc_chars.vref;
  }
  pinMode(CHARGE_PIN, INPUT_PULLUP);
}

float wbBattery::getVoltage() {
  uint16_t v = analogRead(BATT_ADC_PIN);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  return battery_voltage;
}

static float clamp(const float &val, const float &lo, const float &hi) {
  if (val > hi)
    return hi;
  if (val < lo)
    return lo;
  return val;
}

int wbBattery::getPercent() {
  float volts = getVoltage();
  float percentage = (volts - batteryMinV) * 100 / batteryRange;
  return clamp(percentage, 0.0, 100.0);
}

bool wbBattery::isCharging() { return !digitalRead(CHARGE_PIN); }

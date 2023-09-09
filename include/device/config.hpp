#pragma once

#include "esp32-hal-adc.h"
#include "wb/battery_config.hpp"
#include "wb/button_config.hpp"
#include "wb/definitions.hpp"

class DeviceConfig {
public:
  BatteryConfig batConfig{CHARGE_PIN,
                          HIGH,
                          BATT_ADC_PIN,
                          BATTERY_ADC_MAX_VOLTAGE,
                          BATTERY_ADC_MAX_RANGE,
                          BATTERY_VOLTAGE_DIVIDER_COEF,
                          ADC_11db,
                          BATTERY_MIN_V,
                          BATTERY_MAX_V};
  ButtonConfig buttonConfig{TP_PIN_PIN, TP_PWR_PIN, TP_DEBOUNCE_INTERVAL,
                            TP_HELD_DELAY, TP_CLICK_DELAY};
  bool serialEnabled = false;
};

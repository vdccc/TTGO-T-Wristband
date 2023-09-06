#pragma once

#include <Arduino.h>
#include <esp_adc_cal.h>

#include "wb/definitions.hpp"

class wbBattery {
  public:
    void init();
    float getVoltage();
    int getPercent();
    bool isCharging();
  private:
    int vref = 1100;
    const int initVref = 1100;
    const float batteryMinV = 3.2;
    const float batteryMaxV = 4.1;
    const float batteryRange = batteryMaxV - batteryMinV;
};

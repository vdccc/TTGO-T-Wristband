#pragma once

#include "types.hpp"

#define BAT_MAX_PCT 100
#define BAT_MIN_PCT 0

class BatteryConfig {
public:
  BatteryConfig(u8 chrgPin, bool chrgPinPullup, u8 adcPin, float adcMaxV,
                float adcMaxRes, float adcVDivCoef, adcAttenuation adcAtt,
                float batMinV, float batMaxV)
      : chrgPin(chrgPin), chrgPinPullup(chrgPinPullup), adcPin(adcPin),
        adcMaxV(adcMaxV), adcMaxRes(adcMaxRes), adcVDivCoef(adcVDivCoef),
        adcAtt(adcAtt), batMinV(batMinV), batMaxV(batMaxV) {}

  u8 chrgPin;
  bool chrgPinPullup;

  u8 adcPin;
  float adcMaxV;
  float adcMaxRes;
  float adcVDivCoef;
  adcAttenuation adcAtt;

  float batMinV;
  float batMaxV;
};

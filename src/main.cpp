#include <Arduino.h>
#include <Wire.h>
#include <rom/rtc.h>
#include "wristband-tft.hpp"
#include "wristband-ota.hpp"
#include "clock.hpp"
#include "pages.hpp"
#include "mpu.hpp"

__attribute__((__used__))
void setup()
{
  Serial.begin(115200);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(400000);
  initClock();
  tftInit();
#ifndef OTA_ON
  deactivateWifi();
#endif
  btStop();
  setupADC();
#ifndef IMU_SKIP
  initMPU();
#else
  mpuDeepSleep();
#endif
  initButton();
  setupBattery();
#ifdef OTA_ON
  activateWifi();
  setupOTA();
#endif
}

__attribute__((__used__))
void loop()
{
  handleUi();
  updateBatteryChargeStatus();
#ifdef OTA_ON
  otaRunning();
#endif
}

#pragma once

#include <EEPROM.h>
#include <Wire.h>
#include <esp32-hal-gpio.h>
#include <functional>

#include "device/config.hpp"
#include "esp_sleep.h"
#include "wb/battery.hpp"
#include "wb/button.hpp"
#include "wb/clock.hpp"
#include "wb/eeprom.hpp"
#include "wb/mpu.hpp"
#include "wb/wifi.hpp"

// TODO: maybe a base class for all devices will be good

class Device {
public:
  Device();

  void init();
  void sleep();

  // wifi
  static void wifiOn();
  static void wifiOff();
  void wifiConnect(std::string const &apName, std::string const &apPassword);
  static auto wifiEnabled() -> bool;
  static auto wifiConnected() -> bool;
  auto wifiGetRSSI() -> int8_t;
  auto wifiGetSSID() -> std::string;

  // battery
  static auto batteryCharging() -> bool;
  auto batteryPct() -> int;
  auto batteryVoltage() -> float;

  // button
  auto buttonHeld() -> bool;
  auto buttonDoubleClicked() -> bool;
  auto buttonTripleClicked() -> bool;
  auto buttonClicked() -> bool;

  // clock
  auto getDate() -> rtcDate;
  void setDate(rtcDate);

private:
  DeviceConfig config;
  wbButton button;
  wbWifi wifi;
  wbClock clock;
  wbMPU mpu;
  wbEEPROM eeprom;
  wbBattery battery;
};

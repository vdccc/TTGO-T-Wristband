#pragma once

#include <EEPROM.h>
#include <IPAddress.h>
#include <Wire.h>
#include <esp32-hal-gpio.h>
#include <esp_sleep.h>
#include <functional>
#include <sys/_stdint.h>

#include "device/config.hpp"
#include "wb/battery.hpp"
#include "wb/button.hpp"
#include "wb/clock.hpp"
#include "wb/definitions.hpp"
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
  auto wifiGetIP() -> IPAddress;
  auto wifiGetRSSI() -> int8_t;
  auto wifiGetSSID() -> std::string;

  // battery
  static auto batteryCharging() -> bool;
  static auto batteryPct() -> int;
  static auto batteryVoltage() -> float;

  // button
  auto buttonHeld() -> bool;
  auto buttonDoubleClicked() -> bool;
  auto buttonTripleClicked() -> bool;
  auto buttonClicked() -> bool;
  auto buttonIsReady() -> bool;

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

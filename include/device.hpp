#pragma once

#include <EEPROM.h>
#include <Wire.h>
#include <functional>

#include "device/config.hpp"
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
  void wifiOn();
  void wifiOff();
  void wifiConnect(std::string const &apName, std::string const &apPassword);
  bool wifiEnabled();
  bool wifiConnected();

  // battery
  bool batteryCharging();
  int batteryPct();

  // button
  bool buttonHeld();
  bool buttonClicked();

private:
  DeviceConfig config;
  wbButton button;
  wbWifi wifi;
  wbClock clock;
  wbMPU mpu;
  wbEEPROM eeprom;
  wbBattery battery;
};

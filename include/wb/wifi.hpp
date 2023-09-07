#pragma once

#include <WiFi.h>
#include <WiFiType.h>
#include <esp_wifi_types.h>

using std::string;

class wbWifi {
public:
  wbWifi() : wifi(&WiFi) {}

  void init();
  static void enable();
  static void disable();
  static auto is_enabled() -> bool;
  auto connect(std::string const &apName, std::string const &apPwd) -> bool;
  static auto is_connected() -> bool;
  void disconnect();
  auto getRSSI() -> int8_t;
  auto getSSID() -> string;

private:
  WiFiClass *wifi;
};
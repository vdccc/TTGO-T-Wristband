#include "wb/wifi.hpp"
#include "WiFiType.h"
#include "esp_wifi_types.h"

void wbWifi::init() {
  WiFi.setSleep(WIFI_PS_MAX_MODEM);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
}

void wbWifi::enable() { WiFi.mode(WIFI_STA); }

void wbWifi::disable() { WiFi.mode(WIFI_OFF); }

bool wbWifi::is_enabled() { return WiFi.getMode() != WIFI_OFF; }

bool wbWifi::is_connected() { return WiFi.status() == WL_CONNECTED; }

bool wbWifi::connect(std::string const &apName, std::string const &apPwd) {
  return WiFi.begin(apName.c_str(), apPwd.c_str());
}

void wbWifi::disconnect() { WiFi.disconnect(); }

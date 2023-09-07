#include "wb/wifi.hpp"
#include "WiFiType.h"

void wbWifi::init() {
  wifi->setSleep(WIFI_PS_MAX_MODEM);
  wifi->setAutoConnect(true);
  wifi->setAutoReconnect(true);
}

void wbWifi::enable() { WiFiClass::mode(WIFI_STA); }

void wbWifi::disable() { WiFiClass::mode(WIFI_OFF); }

auto wbWifi::is_enabled() -> bool { return WiFiClass::getMode() != WIFI_OFF; }

auto wbWifi::is_connected() -> bool {
  return WiFiClass::status() == WL_CONNECTED;
}

auto wbWifi::connect(std::string const &apName, std::string const &apPwd)
    -> bool {
  return wifi->begin(apName.c_str(), apPwd.c_str()) == WL_CONNECTED;
}

void wbWifi::disconnect() { wifi->disconnect(); }

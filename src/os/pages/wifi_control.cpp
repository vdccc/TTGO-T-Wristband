#include "os/pages/wifi_control.hpp"

void WiFiControl::setup(OSBase &osBase) {}

void WiFiControl::teardown(OSBase &osBase) {}

void WiFiControl::draw(OSBase &osBase) {
  auto device = osBase.getDevice();
  auto gfx = osBase.getGFX();
  if (Device::wifiEnabled()) {
    gfx.drawMessage(0, 0, "WiFi Enabled ");
    std::stringstream wifiRSSI;
    wifiRSSI << "RSSI: " << std::fixed << std::setprecision(3)
             << (int)device.wifiGetRSSI();
    gfx.drawMessage(0, 16, wifiRSSI.str());
    gfx.drawMessage(0, 32, "SSID: " + device.wifiGetSSID());
    std::stringstream ipString{};
    ipString << "IP: " << device.wifiGetIP().toString().c_str();
    gfx.drawMessage(0, 48, ipString.str());
  } else {
    gfx.drawMessage(0, 0, "WiFi Disabled");
  }
}

void WiFiControl::actionHeld(OSBase &osBase) {
  if (Device::wifiEnabled()) {
    Device::wifiOff();
  } else {
    Device::wifiOn();
  }
  osBase.getGFX().drawMessage(0, 48, "Long pressed");
}

void WiFiControl::actionDoubleClick(OSBase &osBase) {}

void WiFiControl::actionTripleClick(OSBase &osBase) {}

auto WiFiControl::available(OSBase & /*osBase*/) -> bool { return true; }

auto WiFiControl::getRefreshInterval() -> int {
  return PAGE_DEFAULT_REFRESH_INTERVAL;
}

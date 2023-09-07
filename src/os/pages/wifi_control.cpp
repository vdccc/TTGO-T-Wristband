#include "os/pages/wifi_control.hpp"

#include "os/base.hpp"
#include "os/pages/page.hpp"

void WiFiControl::draw(OSBase &osBase) {
  auto device = osBase.getDevice();
  auto gfx = osBase.getGFX();
  if (Device::wifiEnabled()) {
    gfx.drawMessage(0, 0, "WiFi Enabled ");
  } else {
    gfx.drawMessage(0, 0, "WiFi Disabled");
  }
}

void WiFiControl::run(OSBase &osBase) {
  auto device = osBase.getDevice();
  if (Device::wifiEnabled()) {
    Device::wifiOff();
  } else {
    Device::wifiOn();
  }
  osBase.getGFX().drawMessage(0, 40, "Long pressed");
}

auto WiFiControl::available() -> bool { return true; }

auto WiFiControl::getRefreshInterval() -> int {
  return PAGE_DEFAULT_REFRESH_INTERVAL;
}

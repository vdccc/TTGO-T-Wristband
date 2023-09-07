#include "os/pages/basic_debug.hpp"

#include <sstream>
#include <string>

#include "os/base.hpp"
#include "os/pages/page.hpp"

void BasicDebug::draw(OSBase &osBase) {
  auto device = osBase.getDevice();
  auto gfx = osBase.getGFX();
  if (Device::wifiEnabled()) {
    gfx.drawMessage(0, 0, "WiFi Enabled ");
  } else {
    gfx.drawMessage(0, 0, "WiFi Disabled");
  }
  if (Device::wifiConnected()) {
    gfx.drawMessage(0, 18, "WiFi Connected   ");
  } else {
    gfx.drawMessage(0, 18, "WiFi Disconnected");
  }
  if (Device::batteryCharging()) {
    gfx.drawMessage(0, 54, "Battery charging");
  } else {
    gfx.drawMessage(0, 54, "                ");
  }
  std::stringstream out{};
  out << device.batteryPct() << "% ";
  gfx.drawMessage(120, 0, out.str());
  std::stringstream sec{};
  sec << millis() / 1000 << "s";
  gfx.drawMessage(100, 40, sec.str());
}

void BasicDebug::run(OSBase &osBase) {
  osBase.getGFX().drawMessage(0, 20, "Long pressed");
}

auto BasicDebug::available() -> bool { return true; }

auto BasicDebug::getRefreshInterval() -> int {
  return PAGE_DEFAULT_REFRESH_INTERVAL;
}

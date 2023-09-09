#include "os/pages/basic_debug.hpp"

#include <iomanip>
#include <sstream>
#include <string>

void BasicDebug::setup(OSBase &osBase) {}

void BasicDebug::teardown(OSBase &osBase) {}

void BasicDebug::draw(OSBase &osBase) {
  auto &device = osBase.getDevice();
  auto &gfx = osBase.getGFX();
  if (Device::wifiEnabled()) {
    gfx.drawMessage(0, 0, "WiFi Enabled ");
  } else {
    gfx.drawMessage(0, 0, "WiFi Disabled");
  }
  if (Device::wifiConnected()) {
    gfx.drawMessage(0, 16, "WiFi Connected   ");
  } else {
    gfx.drawMessage(0, 16, "WiFi Disconnected");
  }
  if (device.batteryCharging()) {
    gfx.drawMessage(0, 64, "Battery charging");
  } else {
    gfx.drawMessage(0, 64, "                ");
  }
  std::stringstream batP{};
  batP << device.batteryPct() << "%";
  gfx.drawMessage(120, 0, batP.str());
  std::stringstream batV{};
  batV << std::fixed << std::setprecision(2) << device.batteryVoltage() << "V";
  gfx.drawMessage(120, 16, batV.str());
  std::stringstream sec{};
  sec << millis() / 1000 << "s";
  gfx.drawMessage(120, 32, sec.str());
}

void BasicDebug::actionHeld(OSBase &osBase) {
  osBase.getGFX().drawMessage(0, 48, "Long pressed");
}

void BasicDebug::actionDoubleClick(OSBase &osBase) {
  osBase.getGFX().drawMessage(0, 48, "Double clicked");
}

void BasicDebug::actionTripleClick(OSBase &osBase) {
  osBase.getGFX().drawMessage(0, 48, "Triple clicked");
}

auto BasicDebug::available(OSBase &osBase) -> bool {
  return osBase.debugActive();
}

auto BasicDebug::getRefreshInterval() -> int {
  return PAGE_DEFAULT_REFRESH_INTERVAL;
}

#include "os/pages/basic_debug.hpp"

#include <sstream>
#include <string>

#include "os/base.hpp"

void BasicDebug::draw(OSBase &os) {
  auto device = os.getDevice();
  auto gfx = os.getGFX();
  if (device.wifiEnabled())
    gfx.drawMessage(0, 0, "WiFi Enabled ");
  else
    gfx.drawMessage(0, 0, "WiFi Disabled");
  if (device.wifiConnected())
    gfx.drawMessage(0, 18, "WiFi Connected   ");
  else
    gfx.drawMessage(0, 18, "WiFi Disconnected");
  if (device.batteryCharging())
    gfx.drawMessage(0, 54, "Battery charging");
  else
    gfx.drawMessage(0, 54, "                ");
  std::stringstream out;
  out << device.batteryPct() << "% ";
  gfx.drawMessage(120, 0, out.str());
  std::stringstream sec;
  sec << millis() / 1000 << "s";
  gfx.drawMessage(100, 40, sec.str());
}

void BasicDebug::run(OSBase &os) {
  os.getGFX().drawMessage(0, 20, "Long pressed");
}

bool BasicDebug::available() { return true; }

int BasicDebug::getRefreshInterval() { return 1000; }

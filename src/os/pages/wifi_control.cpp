#include "os/pages/wifi_control.hpp"

#include "os/base.hpp"

void WiFiControl::draw(OSBase &os) {
  auto device = os.getDevice();
  auto gfx = os.getGFX();
  if (device.wifiEnabled())
    gfx.drawMessage(0, 0, "WiFi Enabled ");
  else
    gfx.drawMessage(0, 0, "WiFi Disabled");
}

void WiFiControl::run(OSBase &os) {
  auto device = os.getDevice();
  if (device.wifiEnabled()) {
    device.wifiOff();
  } else {
    device.wifiOn();
  }
  os.getGFX().drawMessage(0, 40, "Long pressed");
}

bool WiFiControl::available() { return true; }

int WiFiControl::getRefreshInterval() { return 1000; }

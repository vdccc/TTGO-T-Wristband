#include "os/pages/clock.hpp"
#include "os/pages/page.hpp"

using std::stringstream;

void Clock::setup(OSBase &osBase) {
  osBase.getGFX().drawCenterMessage("hello");
  delay(PAGE_DEFAULT_REFRESH_INTERVAL);
}

void Clock::teardown(OSBase &osBase) {
  osBase.getGFX().drawCenterMessage("goodbye!");
  delay(PAGE_DEFAULT_REFRESH_INTERVAL);
}

void Clock::draw(OSBase &osBase) {
  auto &gfx = osBase.getGFX();
  auto &device = osBase.getDevice();
  auto date = device.getDate();
  stringstream hourString{};
  stringstream minuteString{};
  stringstream clockString{};
  hourString << std::setfill('0') << std::setw(2) << (int)date.hour;
  minuteString << std::setfill('0') << std::setw(2) << (int)date.minute;
  clockString << hourString.str() << ":" << minuteString.str();
  gfx.drawBigCenterMessage(clockString.str());
  stringstream batteryString{};
  batteryString << std::setw(4) << (int)device.batteryPct() << "%";
  gfx.drawMessage(100, 0, batteryString.str());
}

void Clock::actionHeld(OSBase &osBase) {
  auto &gfx = osBase.getGFX();
  auto &device = osBase.getDevice();
  auto &ntp = osBase.getNTP();
  if (!Device::wifiConnected()) {
    gfx.drawCenterMessage("WiFi not connected");
    delay(PAGE_DEFAULT_REFRESH_INTERVAL);
    return;
  }
  auto curDate = ntp.getNTPDate();
  device.setDate(curDate);
  gfx.drawCenterMessage("synced");
}

void Clock::actionDoubleClick(OSBase &osBase) {}

void Clock::actionTripleClick(OSBase &osBase) {
  osBase.setDebug(!osBase.debugActive());
}

auto Clock::available(OSBase & /*osBase*/) -> bool { return true; }

auto Clock::getRefreshInterval() -> int {
  return PAGE_DEFAULT_REFRESH_INTERVAL;
}

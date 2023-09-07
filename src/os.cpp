#include "os.hpp"

#include <sstream>

OS::OS()
    : config(), ota(
                    std::bind(&OS::otaStartCallback, this),
                    [this](unsigned int progress, unsigned int total) {
                      this->otaProgressCallback(progress, total);
                    },
                    [this](otaError err) { this->otaErrorCallback(err); }),
      loopTimer(config.loopDelay), sleepTimer(config.sleepDelay) {}

void OS::otaStartCallback() {
  getGFX().drawMessage(0, 36, "OTA STARTING");
  delay(200);
}

void OS::otaProgressCallback(unsigned int progress, unsigned int total) {
  std::stringstream out;
  out << progress << " / " << total;
  getGFX().drawMessage(0, 36, out.str());
}

void OS::otaErrorCallback(otaError err) {
  getGFX().drawMessage(0, 36, "OTA FAILED  ");
  delay(200);
}

void OS::buttonClickCallback() {
  sleepTimer.reset();
  getGFX().blankScreen();
  pages.nextPage();
  loopTimer.set(pages.getCurrentRefreshInterval());
}

void OS::buttonHoldCallback() {
  sleepTimer.reset();
  pages.runCurrentAction(*this);
}

void OS::setup() {
  auto device = getDevice();
  auto gfx = getGFX();
  device.init();
  Device::wifiOn();
  device.wifiConnect(config.apName, config.apPassword);
  ota.init();
  gfx.init();
  loopTimer.set(pages.getCurrentRefreshInterval());
  loopTimer.reset();
  sleepTimer.set(config.sleepDelay);
  sleepTimer.reset();
}

void OS::loop() {
  if (loopTimer.fired()) {
    loopTimer.reset();
    OTA::run();
    auto device = getDevice();
    pages.drawCurrentPage(*this);
    if (device.buttonHeld()) {
      buttonHoldCallback();
    } else if (device.buttonClicked()) {
      buttonClickCallback();
    }
  }
  if (sleepTimer.fired()) {
    sleepTimer.reset();
    getGFX().sleep();
    getDevice().sleep();
  }
}

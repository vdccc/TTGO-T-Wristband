#include "os.hpp"

#include <sstream>

OS::OS()
    : config(), ota([this] { otaStartCallback(); },
                    [this](unsigned int progress, unsigned int total) {
                      otaProgressCallback(progress, total);
                    },
                    [this](otaError err) { otaErrorCallback(err); }),
      loopTimer(config.loopDelay), sleepTimer(config.sleepDelay) {}

void OS::otaStartCallback() {
  gfx.drawMessage(0, 36, "OTA STARTING");
  delay(200);
}

void OS::otaProgressCallback(unsigned int progress, unsigned int total) {
  std::stringstream out;
  out << progress << " / " << total;
  gfx.drawMessage(0, 36, out.str());
}

void OS::otaErrorCallback(otaError err) {
  gfx.drawMessage(0, 36, "OTA FAILED  ");
  delay(200);
}

void OS::buttonClickCallback() {
  sleepTimer.reset();
  gfx.blankScreen();
  pages.nextPage();
  loopTimer.set(pages.getCurrentRefreshInterval());
}

void OS::buttonHoldCallback() {
  sleepTimer.reset();
  pages.runCurrentAction(*this);
}

void OS::setup() {
  device.init();
  device.wifiOn();
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
    ota.run();
    pages.drawCurrentPage(*this);
    if (device.buttonHeld())
      buttonHoldCallback();
    else if (device.buttonClicked())
      buttonClickCallback();
  }
  if (sleepTimer.fired()) {
    sleepTimer.reset();
    gfx.sleep();
    device.sleep();
  }
}

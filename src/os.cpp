#include "os.hpp"

OS::OS()
    : config(), ota(
                    std::bind(&OS::otaStartCallback, this),
                    [this](unsigned int progress, unsigned int total) {
                      this->otaProgressCallback(progress, total);
                    },
                    [this](otaError err) { this->otaErrorCallback(err); }),
      loopTimer(config.loopDelay), sleepTimer(config.sleepDelay) {}

void OS::otaStartCallback() {
  getGFX().blankScreen();
  getGFX().drawCenterMessage("OTA STRT");
  delay(500);
}

void OS::otaProgressCallback(unsigned int progress, unsigned int total) {
  float pct = ((float)progress / (float)total) * 100.0F;
  std::stringstream out;
  out << "OTA: " << std::fixed << std::setprecision(2) << std::setfill(' ')
      << std::setw(6) << pct << "%";
  getGFX().drawCenterMessage(out.str());
}

void OS::otaErrorCallback(otaError err) {
  getGFX().drawCenterMessage("OTA FAIL");
  delay(500);
}

void OS::buttonClickCallback() {
  sleepTimer.reset();
  pages.teardownCurrentPage(*this);
  getGFX().blankScreen();
  pages.nextPage(*this);
  pages.setupCurrentPage(*this);
  pages.drawCurrentPage(*this);
  loopTimer.set(pages.getCurrentRefreshInterval());
}

void OS::buttonDoubleClickCallback() {
  sleepTimer.reset();
  pages.runCurrentActionDoubleClick(*this);
}

void OS::buttonTripleClickCallback() {
  sleepTimer.reset();
  pages.runCurrentActionTripleClick(*this);
}

void OS::buttonHeldCallback() {
  sleepTimer.reset();
  pages.runCurrentActionHeld(*this);
}

void OS::setup() {
  auto &device = getDevice();
  auto &gfx = getGFX();
  device.init();
  gfx.init();
  Device::wifiOn();
  device.wifiConnect(config.apName, config.apPassword);
  ota.init();
  loopTimer.set(pages.getCurrentRefreshInterval());
  sleepTimer.set(config.sleepDelay);
  loopTimer.reset();
  sleepTimer.reset();
}

void OS::loop() {
  auto remainingTime = loopTimer.getRemainingTime();
  if (remainingTime > 0) {
    delay(remainingTime);
  }
  if (loopTimer.fired()) {
    loopTimer.reset();
    OTA::run();
    pages.drawCurrentPage(*this);
    auto &device = getDevice();
    if (device.buttonIsReady()) {
      if (device.buttonClicked()) {
        buttonClickCallback();
      } else if (device.buttonDoubleClicked()) {
        buttonDoubleClickCallback();
      } else if (device.buttonTripleClicked()) {
        buttonTripleClickCallback();
      } else if (device.buttonHeld()) {
        buttonHeldCallback();
      }
    }
  }
  if (sleepTimer.fired()) {
    sleepTimer.reset();
    getGFX().sleep();
    getDevice().sleep();
  }
}

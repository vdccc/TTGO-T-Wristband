#pragma once

#include <sstream>

#include "os/base.hpp"
#include "os/config.hpp"
#include "os/ota.hpp"
#include "os/pages.hpp"
#include "os/timer.hpp"

class OS : OSBase {
public:
  OS();

  void setup();
  void loop();

private:
  OSConfig config;
  OTA ota;
  Pages pages;
  Timer loopTimer;
  Timer sleepTimer;

  void otaStartCallback();
  void otaProgressCallback(unsigned int progress, unsigned int total);
  void otaErrorCallback(otaError err);

  void buttonClickCallback();
  void buttonHoldCallback();
};

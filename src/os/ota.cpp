#include "os/ota.hpp"

void OTA::init() {
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.setPassword(password);
  ArduinoOTA.onStart(std::bind(&OTA::onStart, this))
      .onProgress(progressCallback)
      .onEnd(onEnd)
      .onError(errorCallback);
  ArduinoOTA.begin();
}

void OTA::run() { ArduinoOTA.handle(); }

void OTA::onStart() { startCallback(); }

void OTA::onProgress(unsigned int progress, unsigned int total) {
  progressCallback(progress, total);
}

void OTA::onEnd() { esp_restart(); }

void OTA::onError(otaError err) { errorCallback(err); }

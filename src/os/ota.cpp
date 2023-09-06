#include "os/ota.hpp"

void OTA::init() {
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.setPassword(password);
  ArduinoOTA.onStart([this] { this->onStart(); })
      .onProgress([this](unsigned int progress, unsigned int total) {
        this->onProgress(progress, total);
      })
      .onEnd([this] { this->onEnd(); })
      .onError([this](otaError err) { this->onError(err); });
  ArduinoOTA.begin();
}

void OTA::run() { ArduinoOTA.handle(); }

void OTA::onStart() { startCallback(); }

void OTA::onProgress(unsigned int progress, unsigned int total) {
  progressCallback(progress, total);
}

void OTA::onEnd() { esp_restart(); }

void OTA::onError(otaError err) { errorCallback(err); }

#pragma once

#include <ArduinoOTA.h>
#include <functional>
#include <esp_system.h>

typedef ota_error_t otaError;

class OTA {
public:
  OTA(std::function<void()> start,
      std::function<void(unsigned int, unsigned int)> progress,
      std::function<void(otaError)> error)
      : startCallback(start), progressCallback(progress), errorCallback(error) {};

  void init();
  void run();
  otaError getLastError();

private:
  otaError lastError = OTA_END_ERROR;
  const char *hostname = "t-wrist";
  const char *password = "wristbandpass";

  std::function<void()> startCallback;
  std::function<void(unsigned int, unsigned int)> progressCallback;
  std::function<void(otaError)> errorCallback;

  void onStart();
  void onEnd();
  void onProgress(unsigned int progress, unsigned int total);
  void onError(otaError);
};

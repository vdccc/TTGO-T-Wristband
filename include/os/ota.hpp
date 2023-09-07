#pragma once

#include <ArduinoOTA.h>
#include <esp_system.h>
#include <functional>
#include <utility>

using otaError = ota_error_t;

class OTA {
public:
  OTA(std::function<void()> start,
      std::function<void(unsigned int, unsigned int)> progress,
      std::function<void(otaError)> error)
      : startCallback(std::move(start)), progressCallback(std::move(progress)),
        errorCallback(std::move(error)){};

  void init();
  static void run();
  auto getLastError() -> otaError;

private:
  otaError lastError = OTA_END_ERROR;
  const char *hostname = "t-wrist";
  const char *password = "wristbandpass";

  std::function<void()> startCallback;
  std::function<void(unsigned int, unsigned int)> progressCallback;
  std::function<void(otaError)> errorCallback;

  void onStart();
  static void onEnd();
  void onProgress(unsigned int progress, unsigned int total);
  void onError(otaError);
};

#pragma once

#include <string>

class OSConfig {
public:
  const std::string apName = OS_AP_NAME;
  const std::string apPassword = OS_AP_PASSWORD;
  const unsigned long loopDelay = 1000;
  const unsigned long sleepDelay = 20000;
};

#pragma once

#include <string>

class OSConfig {
public:
  std::string apName = OS_AP_NAME;
  std::string apPassword = OS_AP_PASSWORD;
  unsigned long loopDelay = 1000;
  unsigned long sleepDelay = 20000;
};

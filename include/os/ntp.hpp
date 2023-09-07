#pragma once

#include <NTP.h>
#include <WiFiUdp.h>

#include "../wb/clock.hpp" // FIXME: cut out the rtcDate definition

class osNTP {
public:
  auto getNTPDate() -> rtcDate;

private:
  WiFiUDP con{};
  NTP ntp{con};

  void start();
  void stop();
};

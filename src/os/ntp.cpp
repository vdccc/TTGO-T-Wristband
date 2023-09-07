
#include "os/ntp.hpp" // FIXME: cut out the rtcDate definition
#include "wb/clock.hpp"

void osNTP::start() {
  ntp.begin();
  ntp.update();
}

void osNTP::stop() { ntp.stop(); }

auto osNTP::getNTPDate() -> rtcDate {
  start();
  const rtcDate date{
      static_cast<uint16_t>(ntp.year()),   static_cast<uint8_t>(ntp.month()),
      static_cast<uint8_t>(ntp.day()),     static_cast<uint8_t>(ntp.hours()),
      static_cast<uint8_t>(ntp.minutes()), static_cast<uint8_t>(ntp.seconds())};
  stop();
  return date;
}

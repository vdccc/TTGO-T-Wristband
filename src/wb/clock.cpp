#include "wb/clock.hpp"

void wbClock::init() {
  rtc.begin(Wire);
  rtc.check();
}

void wbClock::sleep() { rtc.disableCLK(); }

auto wbClock::getDateTime() -> rtcDate { return rtc.getDateTime(); }

void wbClock::setDateTime(rtcDate datetime) { rtc.setDateTime(datetime); }

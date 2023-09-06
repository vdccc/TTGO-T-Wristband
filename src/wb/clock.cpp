#include "wb/clock.hpp"

void wbClock::init() {
  rtc.begin(Wire);
  rtc.check();
}

void wbClock::sleep() { rtc.disableCLK(); }

rtcDate wbClock::getDateTime() { return rtc.getDateTime(); }

void wbClock::setDateTime(rtcDate datetime) { rtc.setDateTime(datetime); }

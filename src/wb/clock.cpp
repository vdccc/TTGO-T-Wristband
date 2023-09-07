#include "wb/clock.hpp"

void wbClock::init() {
  rtc.begin(Wire);
  rtc.check();
  rtc.enableCLK(PCF8563_CLK_1HZ);
}

void wbClock::sleep() {
  rtc.disableAlarm();
  // rtc.disableCLK(); NOTE: we need clock :^)
  rtc.disableTimer();
}

auto wbClock::getDateTime() -> rtcDate { return rtc.getDateTime(); }

void wbClock::setDateTime(rtcDate datetime) { rtc.setDateTime(datetime); }

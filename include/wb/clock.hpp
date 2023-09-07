#pragma once

#include <pcf8563.h>

using rtcDate = RTC_Date;

class wbClock {
public:
  void init();
  void sleep();

  auto getDateTime() -> rtcDate;
  void setDateTime(rtcDate);

private:
  PCF8563_Class rtc;
};

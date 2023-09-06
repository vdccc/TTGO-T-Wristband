#pragma once

#include <pcf8563.h>

typedef RTC_Date rtcDate;

class wbClock {
  public:
    void init();
    void sleep();

    rtcDate getDateTime();
    void setDateTime(rtcDate);
    
  private:
    PCF8563_Class rtc;
};

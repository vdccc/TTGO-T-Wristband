#pragma once

#include <esp32-hal.h>

class Timer {
public:
  Timer(unsigned long ms)
      : duration(ms), setTime(millis() + ms), startTime(millis()), runTime(0) {}

  void reset();
  void set(unsigned long ms);
  bool fired();
  unsigned long getRunTime();

private:
  unsigned long duration;
  unsigned long setTime;
  unsigned long startTime;
  unsigned long runTime;
};

#pragma once

#include <esp32-hal.h>

class Timer {
public:
  Timer(unsigned long delay)
      : duration(delay), setTime(millis() + delay), startTime(millis()) {}

  void reset();
  void set(unsigned long delay);
  auto fired() -> bool;
  auto getRunTime() const -> unsigned long;

private:
  unsigned long duration;
  unsigned long setTime;
  unsigned long startTime;
  unsigned long runTime{};
};

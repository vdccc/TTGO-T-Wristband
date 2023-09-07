#include "os/timer.hpp"

void Timer::reset() {
  startTime = millis();
  setTime = startTime + duration;
}

void Timer::set(unsigned long delay) {
  duration = delay;
  setTime = millis() + duration;
}

auto Timer::fired() -> bool {
  unsigned long const curTime = millis();
  if (curTime > setTime) {
    runTime = curTime - startTime;
    return true;
  }
  return false;
}

auto Timer::getRunTime() const -> unsigned long { return runTime; }

auto Timer::getRemainingTime() const -> unsigned long {
  auto curTime = millis();
  if (curTime > setTime) {
    return 0;
  }
  return setTime - curTime;
};

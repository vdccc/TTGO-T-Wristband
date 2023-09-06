#include "os/timer.hpp"

void Timer::reset() {
  startTime = 0;
  setTime = millis() + duration;
}

void Timer::set(unsigned long ms) {
  duration = ms;
  setTime = millis() + duration;
}

bool Timer::fired() {
  unsigned long curTime = millis();
  if (curTime > setTime) {
    runTime = curTime - startTime;
    return true;
  }
  return false;
}

unsigned long Timer::getRunTime() { return runTime; }

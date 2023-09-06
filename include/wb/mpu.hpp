#pragma once

#include "MPU9250.hpp"

// TODO: implement accel
// TODO: implement compass

class wbMPU {
  public:
    void init();
    void sleep();
    void deepSleep();

  private:
    MPU9250 mpu;
};

#pragma once

#include "device.hpp"
#include "os/gfx.hpp"
#include "os/ntp.hpp"

class OSBase {
public:
  auto getDevice() -> Device &;
  auto getGFX() -> GFX &;
  auto getNTP() -> osNTP &;

private:
  Device device;
  GFX gfx;
  osNTP ntp;
};

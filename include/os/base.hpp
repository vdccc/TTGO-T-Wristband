#pragma once

#include "device.hpp"
#include "os/gfx.hpp"

class OSBase {
public:
  auto getDevice() -> Device &;
  auto getGFX() -> GFX &;

private:
  Device device;
  GFX gfx;
};

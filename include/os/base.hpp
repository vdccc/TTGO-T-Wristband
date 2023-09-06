#pragma once

#include "device.hpp"
#include "os/gfx.hpp"

class OSBase {
public:
  Device &getDevice();
  GFX &getGFX();

protected:
  Device device;
  GFX gfx;
};

#pragma once

#include "device.hpp"
#include "os/gfx.hpp"
#include "os/ntp.hpp"

class OSBase {
public:
  auto getDevice() -> Device &;
  auto getGFX() -> GFX &;
  auto getNTP() -> osNTP &;
  auto debugActive() const -> bool;
  void setDebug(bool);

private:
  Device device;
  GFX gfx;
  osNTP ntp;

  bool debug{true};
};

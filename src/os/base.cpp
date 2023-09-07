#include "os/base.hpp"

auto OSBase::getDevice() -> Device & { return device; }

auto OSBase::getGFX() -> GFX & { return gfx; }

auto OSBase::getNTP() -> osNTP & { return ntp; }
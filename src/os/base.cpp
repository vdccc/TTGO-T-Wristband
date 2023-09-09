#include "os/base.hpp"

auto OSBase::getDevice() -> Device & { return device; }

auto OSBase::getGFX() -> GFX & { return gfx; }

auto OSBase::getNTP() -> osNTP & { return ntp; }

auto OSBase::debugActive() const -> bool { return debug; }

void OSBase::setDebug(bool debugActive) { debug = debugActive; }
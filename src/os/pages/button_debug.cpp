#include "os/pages/button_debug.hpp"
#include "os/pages/page.hpp"

void setup(OSBase &osBase) {}
void teardown(OSBase &osBase) {}
void draw(OSBase &osBase) { auto &gfx = osBase.getGFX(); }
void actionHeld(OSBase &osBase) {}
void actionDoubleClick(OSBase &osBase) {}
void actionTripleClick(OSBase &osBase) {}
auto available() -> bool { return true; }
auto getRefreshInterval() -> int { return PAGE_DEFAULT_REFRESH_INTERVAL; }

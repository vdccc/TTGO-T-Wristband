#pragma once

#include <initializer_list>
#include <map>
#include <memory>
#include <vector>

#include "os/pages/basic_debug.hpp"
#include "os/pages/clock.hpp"
#include "os/pages/wifi_control.hpp"

// better name would be actions or apps :^)
class Pages {
public:
  Pages();
  Pages(std::initializer_list<Page *>);

  void setupCurrentPage(OSBase &osBase);
  void teardownCurrentPage(OSBase &osBase);
  void drawCurrentPage(OSBase &osBase);
  void runCurrentActionHeld(OSBase &osBase);
  void runCurrentActionDoubleClick(OSBase &osBase);
  void runCurrentActionTripleClick(OSBase &osBase);
  auto getCurrentRefreshInterval() -> int;
  void nextPage(OSBase &osBase);
  void pushPage(std::unique_ptr<Page> page);

private:
  std::vector<std::unique_ptr<Page>> pages{};
  size_t curPageIDX;
};

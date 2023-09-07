#pragma once

#include <iomanip>
#include <sstream>

#include "os/pages/page.hpp"

class Clock final : public Page {
public:
  void setup(OSBase &osBase) final;
  void teardown(OSBase &osBase) final;
  void draw(OSBase &osBase) final;
  void run(OSBase &osBase) final;
  auto available() -> bool final;
  auto getRefreshInterval() -> int final;
};

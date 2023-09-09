#pragma once

#include "os/pages/page.hpp"

class BasicDebug final : public Page {
public:
  void setup(OSBase &osBase) final;
  void teardown(OSBase &osBase) final;
  void draw(OSBase &osBase) final;
  void actionHeld(OSBase &osBase) final;
  void actionDoubleClick(OSBase &osBase) final;
  void actionTripleClick(OSBase &osBase) final;
  auto available(OSBase &osBase) -> bool final;
  auto getRefreshInterval() -> int final;
};

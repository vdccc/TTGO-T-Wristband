#pragma once

#include "os/pages/page.hpp"

class BasicDebug final : public Page {
public:
  void draw(OSBase &osBase) final;
  void run(OSBase &osBase) final;
  auto available() -> bool final;
  auto getRefreshInterval() -> int final;
};

#pragma once

#include "os/base.hpp"

#define PAGE_DEFAULT_REFRESH_INTERVAL 1000

class Page {
public:
  virtual ~Page() = default;
  virtual void setup(OSBase &osBase) = 0;
  virtual void teardown(OSBase &osBase) = 0;
  virtual void draw(OSBase &osBase) = 0;
  virtual void actionHeld(OSBase &osBase) = 0;
  virtual void actionDoubleClick(OSBase &osBase) = 0;
  virtual void actionTripleClick(OSBase &osBase) = 0;
  virtual auto available() -> bool = 0;
  virtual auto getRefreshInterval() -> int = 0;
};

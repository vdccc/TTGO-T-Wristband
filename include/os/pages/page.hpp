#pragma once

#include "os/base.hpp"

#define PAGE_DEFAULT_REFRESH_INTERVAL 1000

class Page {
public:
  virtual ~Page() = default;
  virtual void draw(OSBase &osBase) = 0;
  virtual void run(OSBase &osBase) = 0;
  virtual auto available() -> bool = 0;
  virtual auto getRefreshInterval() -> int = 0;
};

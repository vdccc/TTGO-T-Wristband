#pragma once

#include "os/base.hpp"

class Page {
public:
  virtual void draw(OSBase &os) = 0;
  virtual void run(OSBase &os) = 0;
  virtual bool available() = 0;
  virtual int getRefreshInterval() = 0;
};

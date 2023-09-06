#pragma once

#include "os/pages/page.hpp"

class BasicDebug final : public Page {
public:
  virtual void draw(OSBase &os) override final;
  virtual void run(OSBase &os) override final;
  virtual bool available() override final;
  virtual int getRefreshInterval() override final;
};

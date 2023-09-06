#pragma once

#include <EEPROM.h>
#include <cstddef>

class wbEEPROM {
  public:
    void init();
    void read(int addr, void *dst, size_t size);
    void write(int addr, void *src, size_t size);
  private:
};

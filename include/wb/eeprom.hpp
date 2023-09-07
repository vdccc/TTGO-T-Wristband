#pragma once

#include <EEPROM.h>
#include <cstddef>

class wbEEPROM {
public:
  void init();
  static void read(int addr, void *dst, size_t size);
  static void write(int addr, void *src, size_t size);
};

#include "wb/eeprom.hpp"

#include "EEPROM.h"

void wbEEPROM::init() {}

void wbEEPROM::read(int addr, void *dst, size_t size) {
  EEPROM.begin(size);
  EEPROM.readBytes(addr, dst, size);
  EEPROM.end();
}

void wbEEPROM::write(int addr, void *src, size_t size) {
  EEPROM.begin(size);
  EEPROM.writeBytes(addr, src, size);
  EEPROM.commit();
  EEPROM.end();
}

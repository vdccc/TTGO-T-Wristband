#pragma once

#include <TFT_eSPI.h>
#include <esp32-hal-ledc.h>

#include "wb/definitions.hpp"

class GFX {
public:
  void init();
  void sleep();

  void drawMessage(int posX, int posY, std::string const &msg);
  void blankScreen();
  static void setBrightness(int brightness);

private:
  TFT_eSPI tft;

  int brightness = TFT_DEFAULT_BRIGHTNESS;

  static auto clamp(int val) -> int;
};

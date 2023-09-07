#pragma once

#include "wb/definitions.hpp"

#include <TFT_eSPI.h>

class GFX {
public:
  void init();
  void sleep();

  void drawMessage(int posX, int posY, std::string const &&msg);
  void drawCenterMessage(std::string const &&msg);
  void drawBigCenterMessage(std::string const &&msg);
  void blankScreen();
  static void setBrightness(int brightness);

private:
  TFT_eSPI tft{};

  int brightness = TFT_DEFAULT_BRIGHTNESS;

  static auto clamp(int val) -> int;
};

#pragma once

#include <TFT_eSPI.h>
#include <esp32-hal-ledc.h>

#include "wb/definitions.hpp"

class GFX {
public:
  GFX() : tft(TFT_eSPI()) {}

  const int brightness_min = 0;
  const int brightness_max = 255;

  void init();
  void sleep();

  void setBrightness(int brightness);
  void drawMessage(int x, int y, std::string const &msg);
  void blankScreen();

private:
  TFT_eSPI tft;

  int brightness = 185;

  int clamp(int a);
};

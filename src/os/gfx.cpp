#include "TFT_eSPI.h"
#include "wb/definitions.hpp"
#include <os/gfx.hpp>

void GFX::init() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  blankScreen();
  ledcSetup(TFT_LEDC_CHAN, TFT_LEDC_FREQ, TFT_LEDC_RESOLUTION);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(TFT_LEDC_CHAN, 185);
}

void GFX::sleep() {
  blankScreen();
  tft.writecommand(ST7735_SWRESET);
  delay(100);
  tft.writecommand(ST7735_SLPIN);
  delay(150);
  tft.writecommand(ST7735_DISPOFF);
}

int GFX::clamp(int a) {
  if (a > brightness_max)
    return brightness_max;
  if (a < brightness_min)
    return brightness_min;
  return a;
}

void GFX::setBrightness(int brightness) {
  ledcWrite(TFT_LEDC_CHAN, clamp(brightness));
}

void GFX::blankScreen() { tft.fillScreen(TFT_BLACK); }

void GFX::drawMessage(int x, int y, std::string const &msg) {
  tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
  tft.drawString(msg.c_str(), x, y, 2);
}

#include "os/gfx.hpp"
#include "TFT_eSPI.h"

void GFX::init() {
  tft.init();
  tft.setRotation(1);
  blankScreen();
  ledcSetup(TFT_LEDC_CHAN, TFT_LEDC_FREQ, TFT_LEDC_RESOLUTION);
  ledcAttachPin(TFT_BL, TFT_LEDC_CHAN);
  ledcWrite(TFT_LEDC_CHAN, brightness);
}

void GFX::sleep() {
  blankScreen();
  drawMessage(tft.width() / 2, tft.height() / 2, "going to sleep");
  delay(1000);
  tft.writecommand(TFT_SWRST);
  delay(TFT_ST7735_SWRESET_DELAY);
  tft.writecommand(ST7735_SLPIN);
  delay(TFT_ST7735_SLPIN_DELAY);
  tft.writecommand(ST7735_DISPOFF);
}

auto GFX::clamp(int val) -> int {
  if (val > TFT_MAX_BRIGHTNESS) {
    return TFT_MAX_BRIGHTNESS;
  }
  if (val < TFT_MIN_BRIGHTNESS) {
    return TFT_MIN_BRIGHTNESS;
  }
  return val;
}

void GFX::setBrightness(int brightness) {
  ledcWrite(TFT_LEDC_CHAN, clamp(brightness));
}

void GFX::blankScreen() { tft.fillScreen(TFT_BLACK); }

void GFX::drawMessage(int posX, int posY, std::string const &msg) {
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString(msg.c_str(), posX, posY, 2);
}

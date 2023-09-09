#include "os/gfx.hpp"
#include "wb/definitions.hpp"

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
  tft.setTextDatum(MC_DATUM);
  drawCenterMessage("going to sleep");
  delay(800);
  blankScreen();
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

void GFX::blankScreen() { tft.fillScreen(TFT_SKYBLUE); }

void GFX::drawBigCenterMessage(std::string const &&msg) {
  tft.setTextColor(GFX_DEFAULT_FG, GFX_DEFAULT_BG);
  tft.setTextDatum(CC_DATUM);
  tft.drawString(msg.c_str(), tft.width() / 2, tft.height() / 2, 6);
}

void GFX::drawCenterMessage(std::string const &&msg) {
  tft.setTextColor(GFX_DEFAULT_FG, GFX_DEFAULT_BG);
  tft.setTextDatum(CC_DATUM);
  tft.drawString(msg.c_str(), tft.width() / 2, tft.height() / 2, 2);
}

void GFX::drawMessage(int posX, int posY, std::string const &msg) {
  drawMessage(posX, posY, msg, GFX_DEFAULT_FG, GFX_DEFAULT_BG, 2);
}

void GFX::drawMessage(int posX, int posY, std::string const &msg, int fgColor,
                      int bgColor, int font) {
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(fgColor, bgColor);
  tft.drawString(msg.c_str(), posX, posY, 2);
}

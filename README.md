# Sepples-os for TTGO-Wrist-Band

very modern non-multitasking os for t-wristband :^)

## build 

`pio run`

## WiFi settings

Either use `-DOS_AP_NAME=\"<ssid>\"` `-DOS_AP_PASSWORD=\"<password>\"` in `build_flasg` in `platformio.ini`.
Or just set them in `include/os/config.hpp`.

## upload over OTA

Remember to set matching password in `include/os/ota.hpp` and `platformio.ini`.
Currently there is no page to display wristband IP so you have to guess :^), set it to correct value in `platformio.ini`.

`pio run -t upload`

## upload over serial

`pio run -t upload -e esp32devSerial`

## adding your pages

Base class for page is `include/os/pages/page.hpp`.
Example class is `include/os/pages/basic_debug.hpp`.
Register it in `src/os/pages.cpp` `Pages::Pages()` constructor.
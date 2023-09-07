#include "device.hpp"
#include "wb/definitions.hpp"

Device::Device()
    : config(),
      button(config.buttonHoldTime, config.buttonPin, config.buttonDebounceTime,
             config.buttonPullup, config.buttonALow),
      battery() {}

void Device::init() {
  if (config.serialEnabled) {
    Serial.begin(SERIAL_BIT_RATE_DEFAULT);
  }
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(I2C_DEFAULT_CLOCK);
  wifi.init();
  clock.init();
  mpu.init();
  mpu.sleep();
  eeprom.init();
  battery.init();
  button.init();
}

void Device::sleep() {
  wifi.disconnect();
  wbWifi::disable();
  clock.sleep();
  mpu.deepSleep();
  esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_disable_rom_logging();
  esp_deep_sleep_start();
}

void Device::wifiOn() { wbWifi::enable(); }

void Device::wifiOff() { wbWifi::disable(); }

void Device::wifiConnect(std::string const &apName,
                         std::string const &apPassword) {
  wifi.connect(apName, apPassword);
}

auto Device::wifiConnected() -> bool { return wbWifi::is_connected(); }

auto Device::wifiEnabled() -> bool { return wbWifi::is_enabled(); }

auto Device::batteryCharging() -> bool { return wbBattery::isCharging(); }

auto Device::batteryPct() -> int { return battery.getPercent(); }

auto Device::buttonHeld() -> bool { return button.held(); }

auto Device::buttonClicked() -> bool { return button.clicked(); }

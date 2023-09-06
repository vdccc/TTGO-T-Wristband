#include "device.hpp"

Device::Device()
    : config(),
      button(config.buttonHoldTime, config.buttonPin, config.buttonDebounceTime,
             config.buttonPullup, config.buttonALow) {}

void Device::init() {
  if (config.serialEnabled)
    Serial.begin(115200);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(400000);
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
  wifi.disable();
  clock.sleep();
  mpu.deepSleep();
  esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_disable_rom_logging();
  esp_deep_sleep_start();
}

void Device::wifiOn() { wifi.enable(); }

void Device::wifiOff() { wifi.disable(); }

void Device::wifiConnect(std::string const &apName,
                         std::string const &apPassword) {
  wifi.connect(apName, apPassword);
}

bool Device::wifiConnected() { return wifi.is_connected(); }

bool Device::wifiEnabled() { return wifi.is_enabled(); }

bool Device::batteryCharging() { return battery.isCharging(); }

int Device::batteryPct() { return battery.getPercent(); }

bool Device::buttonHeld() { return button.held(); }

bool Device::buttonClicked() { return button.clicked(); }

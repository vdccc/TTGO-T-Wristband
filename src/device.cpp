#include "device.hpp"

Device::Device()
    : config(), button(config.buttonConfig), battery(config.batConfig) {}

void Device::init() {
  if (config.serialEnabled) {
    Serial.begin(SERIAL_BIT_RATE_DEFAULT);
  }
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(I2C_DEFAULT_CLOCK);
  clock.init();
  mpu.init();
  mpu.sleep();
  eeprom.init();
  battery.init();
  button.init();
  wifi.init();
}

void Device::sleep() {
  wifi.disconnect();
  wbWifi::disable();
  clock.sleep();
  mpu.deepSleep();
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, HIGH);
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

auto Device::wifiGetIP() -> IPAddress { return wifi.getIP(); }

auto Device::wifiGetRSSI() -> int8_t { return wifi.getRSSI(); }

auto Device::wifiGetSSID() -> std::string { return wifi.getSSID(); }

auto Device::batteryCharging() -> bool { return battery.isCharging(); }

auto Device::batteryPct() -> u8 { return battery.getPercent(); }

auto Device::batteryVoltage() -> float { return battery.getVoltage(); }

auto Device::buttonHeld() -> bool { return button.held(); }

auto Device::buttonClicked() -> bool { return button.clicked(); }

auto Device::buttonDoubleClicked() -> bool { return button.doubleClicked(); }

auto Device::buttonTripleClicked() -> bool { return button.tripleClicked(); }

auto Device::buttonIsReady() -> bool { return button.ready(); }

auto Device::getDate() -> rtcDate { return clock.getDateTime(); }

void Device::setDate(rtcDate date) { clock.setDateTime(date); }

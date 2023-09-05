#include "wristband-wifi.hpp"
#include "wristband-tft.hpp"

void configModeCallback(WiFiManager *myWiFiManager)
{
  char apName[50] = " ";
  myWiFiManager->getConfigPortalSSID().toCharArray(apName, 50);
  wifiManagerAdvice(apName);
}

void setupWiFi()
{
  WiFiManager wifiManager;
  wifiManager.preloadWiFi("qwerty6", "1337SUPERultrawifi_+");
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setBreakAfterConfig(true);
  #ifdef OTA_ON
  wifiManager.setConfigPortalTimeout(10);
  while (!wifiManager.autoConnect("T-Wristband")) {
    msgError("wifi f. r.");
    delay(100);
  }
  #else
  wifiManager.autoConnect("T-Wristband");
  #endif
}

void activateWifi()
{
  WiFi.mode(WIFI_STA);
  if (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
  }
}

void deactivateWifi()
{
  WiFi.mode(WIFI_OFF);
}
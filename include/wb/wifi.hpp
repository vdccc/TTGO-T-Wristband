#pragma once

#include <WiFi.h>

class wbWifi {
public:
  wbWifi() {}

  void init();
  void enable();
  void disable();
  bool is_enabled();
  bool connect(std::string const &apName, std::string const &apPwd);
  bool is_connected();
  void disconnect();

private:
};
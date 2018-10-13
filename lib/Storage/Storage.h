#ifndef Storage_h
#define Storage_h

#include <Arduino.h>
#include <EEPROM.h>

class Storage {

public:
  void run(void);
  void setSsid(String ssid);
  void setPass(String pass);
  void clear();
  String getPass();
  String getSsid();
};

#endif

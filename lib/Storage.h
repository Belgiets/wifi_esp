#include <Arduino.h>
#include <EEPROM.h>

class Storage {
public:
  void setSsid(String ssid) {
    for (int i = 0; i < ssid.length(); ++i) {
      EEPROM.write(i, ssid[i]);
    }

    EEPROM.commit();
  }

  String getSsid() {
    String ssid;

    for (int i = 0; i < 32; ++i) {
      ssid += char(EEPROM.read(i));
    }

    return ssid;
  }

  void setPass(String pass) {
    for (int i = 0; i < pass.length(); ++i) {
      EEPROM.write(32 + i, pass[i]);
    }

    EEPROM.commit();
  }

  String getPass() {
    String ssid;

    for (int i = 0; i < 64; ++i) {
      ssid += char(EEPROM.read(32 + i));
    }

    return ssid;
  }
};

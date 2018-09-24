#include <Arduino.h>
#include <EEPROM.h>

class Storage {
public:
  void setSsid(String ssid) {
    for (int i = 0; i < 32; ++i) {
      if (i < ssid.length()) {
        EEPROM.write(i, ssid[i]);
      } else {
        EEPROM.write(i, LOW);
      }
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
    for (int i = 0; i < 64; ++i) {
      if (i < pass.length()) {
        EEPROM.write(32 + i, pass[i]);
      } else {
        EEPROM.write(32 + i, LOW);
      }

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

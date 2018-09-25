#include <Arduino.h>
#include <EEPROM.h>

class Storage {
public:
  void setSsid(String ssid) {
    for (int i = 0; i < 32; ++i) {
      if (i < int(ssid.length())) {
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
      char byte = char(EEPROM.read(i));

      if (byte != LOW) {
        ssid += byte;
      }
    }

    return ssid;
  }

  void setPass(String pass) {
    for (int i = 0; i < 64; ++i) {
      if (i < int(pass.length())) {
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
      char byte = char(EEPROM.read(32 + i));

      if (byte != LOW) {
        ssid += byte;
      }
    }

    return ssid;
  }
};

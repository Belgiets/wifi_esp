#include "Storage.h"
#include <Arduino.h>
#include <EEPROM.h>

void Storage::run() { EEPROM.begin(128); }

void Storage::setSsid(String ssid) {
  for (int i = 0; i < 32; ++i) {
    if (i < int(ssid.length())) {
      EEPROM.write(i, ssid[i]);
    } else {
      EEPROM.write(i, LOW);
    }
  }

  EEPROM.commit();
};

void Storage::setPass(String pass) {
  for (int i = 0; i < 64; ++i) {
    if (i < int(pass.length())) {
      EEPROM.write(32 + i, pass[i]);
    } else {
      EEPROM.write(32 + i, LOW);
    }

    EEPROM.write(32 + i, pass[i]);
  }

  EEPROM.commit();
};

void Storage::clear() {
  for (int i = 0; i < 96; ++i) {
    EEPROM.write(i, LOW);
  }
}

String Storage::getSsid() {
  String ssid;

  for (int i = 0; i < 32; ++i) {
    char byte = char(EEPROM.read(i));

    if (byte != LOW) {
      ssid += byte;
    }
  }

  return ssid;
}

String Storage::getPass() {
  String ssid;

  for (int i = 0; i < 64; ++i) {
    char byte = char(EEPROM.read(32 + i));

    if (byte != LOW) {
      ssid += byte;
    }
  }

  return ssid;
}

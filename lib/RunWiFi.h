#include "../lib/Storage.h"
#include <ESP8266WiFi.h>

class RunWiFi {
private:
  IPAddress ip;
  IPAddress gw;
  IPAddress sm;
  Storage eeprom;

public:
  RunWiFi(IPAddress ipAP, IPAddress ipGateway, IPAddress subnetMask,
          Storage storage) {
    ip = ipAP;
    gw = ipGateway;
    sm = subnetMask;
    eeprom = storage;
  };

  void run() {}

  void connect() {
    String ssid = eeprom.getSsid();
    String pass = eeprom.getPass();
  }

  void runAP() {
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(ip, gw, sm) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP("esp-ssid", "kotShpr0t") ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP().toString());
  }
};

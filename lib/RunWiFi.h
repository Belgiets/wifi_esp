#include <ESP8266WiFi.h>

class RunWiFi {
private:
  IPAddress ip;
  IPAddress gw;
  IPAddress sm;

public:
  RunWiFi(IPAddress ipAP, IPAddress ipGateway, IPAddress subnetMask) {
    ip = ipAP;
    gw = ipGateway;
    sm = subnetMask;
  };

  void run() {
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(ip, gw, sm) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP("esp-ssid", "kotShpr0t") ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP().toString());
  }
};

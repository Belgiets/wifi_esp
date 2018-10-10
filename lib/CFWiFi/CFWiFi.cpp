#include "CFWiFi.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

CFWiFi::CFWiFi(IPAddress ipAP, IPAddress ipGateway, IPAddress subnetMask) {
  _ipAP = ipAP;
  _ipGateway = ipGateway;
  _subnetMask = subnetMask;
};

void CFWiFi::runAP(void) {
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(_ipAP, _ipGateway, _subnetMask) ? "Ready"
                                                                   : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("esp-ssid", "kotShpr0t") ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP().toString());
};

void CFWiFi::stopAP(void) { WiFi.softAPdisconnect(true); };

void CFWiFi::connectToAP(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

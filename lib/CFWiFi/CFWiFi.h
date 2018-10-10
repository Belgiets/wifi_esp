#ifndef CFWiFi_h
#define CFWiFi_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class CFWiFi {
private:
  IPAddress _ipAP;
  IPAddress _ipGateway;
  IPAddress _subnetMask;

public:
  CFWiFi(IPAddress ipAP, IPAddress ipGateway, IPAddress subnetMask);
  void runAP(void);
  void stopAP(void);
  void connectToAP(String ssid, String password);
};

#endif

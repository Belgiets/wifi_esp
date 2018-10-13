#ifndef WSHtml_h
#define WSHtml_h

#include <Arduino.h>

class WSHtml {

public:
  String body(String content, String header);
  String formWifiCreds();
  String selectSsid();
};

#endif

#include "WSHtml.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

String WSHtml::body(String content, String header) {
  String body;

  body += "<!DOCTYPE HTML>\r\n";
  body += "<html>";
  body += "<meta charset='UTF-8'>";
  body += "<meta name='viewport'";
  body += " content='width=device-width, initial-scale=1.0'>";
  body += "<h1>";
  body += header;
  body += "</h1>";
  body += content;
  body += "</html>";

  return body;
}

String WSHtml::formWifiCreds() {
  String form;

  form = "<form method='get' action='setting'>";
  form += "<p><label>SSID:</label></p>";
  form += selectSsid();
  form += "<p><label>Password:</label></p>";
  form += "<p><input name='pass' length=64></p>";
  form += "<p><input type='submit' value='Connect'></p>";
  form += "</form>";

  return form;
};

String WSHtml::selectSsid() {
  String select;

  int n = WiFi.scanNetworks();
  if (n < 1) {
    select += "No wifi networks found";
  } else {
    select += "<div><select name='ssid'>";
    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);

      select += "<option value='" + ssid + "'>";
      select += ssid;
      select += " (";
      select += WiFi.RSSI(i);
      select += ")";
      select += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
      select += "</option>";
    }
    select += "</select></div>";
  }

  return select;
};

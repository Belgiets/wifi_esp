#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);
IPAddress apIP;

void createWebServer() {
  server.on("/", []() {
    String st;
    String content;

    int n = WiFi.scanNetworks();
    if (n < 1) {
      st += "No wifi networks found";
    } else {
      st += "<select name='ssid'>";
      for (int i = 0; i < n; ++i) {
        String ssid = WiFi.SSID(i);

        st += "<option value='" + ssid + "'>";
        st += ssid;
        st += " (";
        st += WiFi.RSSI(i);
        st += ")";
        st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
        st += "</option>";
      }
      st += "</select>";
    }

    content += "<!DOCTYPE HTML>\r\n<html><h1>Cat feeder AP</h1> ";
    content += "<form method='get' action='setting'><label>SSID:</label>";
    content += st;
    content += "<input name='pass' length=64><input type='submit'></form>";
    content += "</html>";
    server.send(200, "text/html", content);
  });

  server.on("/setting", []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    Serial.println(ssid);
    Serial.println("");
    Serial.println(pass);
    Serial.println("");

    server.send(200, "text/html", "Server has got config");
  });

  server.begin();
}

void setup() {
  Serial.begin(9600);
  apIP = WiFi.softAP("esp-ssid", "kotShpr0t");
  createWebServer();
}

void loop() {
  Serial.print(apIP.toString());
  delay(5000);
}

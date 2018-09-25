#include "../lib/RunWiFi.h"
#include "../lib/Storage.h"
#include "../lib/WebServerHtml.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);
IPAddress ipAP(10, 0, 1, 1);
IPAddress ipGateway(10, 0, 1, 1);
IPAddress subnetMask(255, 255, 255, 0);
Storage storage;
RunWiFi wf(ipAP, ipGateway, subnetMask, storage);
WebServerHtml html;

void createWebServer() {
  server.on("/", []() {
    String form = html.formWifiCreds();
    String body = html.body(form, "Cat feeder: WiFi settings");

    server.send(200, "text/html", body);
  });

  server.on("/setting", []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    if (ssid.length() > 0) {
      storage.setSsid(ssid);
    }

    if (pass.length() > 0) {
      storage.setPass(pass);
    }

    server.send(200, "text/html", "Server has got config");
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(128);
  delay(2000);

  Serial.println(WiFi.softAPIP());

  // wf.run();
  // createWebServer();
}

void loop() { server.handleClient(); }

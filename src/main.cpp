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
RunWiFi wf(ipAP, ipGateway, subnetMask);
WebServerHtml html;
Storage flash;

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
      flash.setSsid(ssid);
    }

    if (pass.length() > 0) {
      flash.setPass(pass);
    }

    Serial.println("ssid");
    Serial.println(flash.getSsid());
    Serial.println("pass");
    Serial.println(flash.getPass());

    server.send(200, "text/html", "Server has got config");
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(128);
  delay(2000);

  Serial.println(flash.getSsid());
  Serial.println(flash.getPass());

  wf.run();
  createWebServer();
}

void loop() { server.handleClient(); }

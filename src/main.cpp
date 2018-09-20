#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);
IPAddress ipLocal(10, 0, 1, 1);
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void createWebServer() {
  server.on("/", []() {
    String st;
    String content;

    int n = WiFi.scanNetworks();
    if (n < 1) {
      st += "No wifi networks found";
    } else {
      st += "<div><select name='ssid'>";
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
      st += "</select></div>";
    }

    content += "<!DOCTYPE HTML>\r\n<html><meta charset='UTF-8'><meta name=";
    content += "'viewport' content='width=device-width, initial-scale=1.0'>";
    content += "<h1>Cat feeder AP</h1><form method='get' action='setting'>";
    content += "<p><label>SSID:</label></p>";
    content += st;
    content += "<p><label>Password:</label></p><p><input name='pass' length=64";
    content += "></p><p><input type='submit' value='Connect'></p>";
    content += "</form></html>";
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
  Serial.begin(115200);
  delay(2000);

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(ipLocal, gateway, subnet) ? "Ready"
                                                             : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("esp-ssid", "kotShpr0t") ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP().toString());
  createWebServer();
}

void loop() { server.handleClient(); }

#include <Arduino.h>
#include <CFServo.h>
#include <CFWiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FBDB.h>
#include <Storage.h>
#include <WSHtml.h>

ESP8266WebServer server(80);
IPAddress ipAP(10, 0, 1, 1);
IPAddress ipGateway(10, 0, 1, 1);
IPAddress subnetMask(255, 255, 255, 0);
Storage storage;
CFWiFi wf(ipAP, ipGateway, subnetMask);
WSHtml html;
FBDB firebaseDB("cat-feeder-a11ed.firebaseio.com", "actions/feed");
CFServo cfServo(4);

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

    if (ssid.length() > 0) {
      wf.stopAP();
      Serial.println("AP has been stopped");
      wf.connectToAP(ssid, pass);
    }

    server.send(200, "text/html", "Server has got config");
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);
  storage.run();
  delay(2000);

  String ssid = storage.getSsid();
  String pass = storage.getPass();

  if (ssid.length() > 0) {
    if (wf.connectToAP(ssid, pass)) {
      firebaseDB.begin();
      cfServo.setup();
      Serial.println("WiFi connected");
    } else {
      storage.clear();
      wf.runAP();
      Serial.println("Storage was cleared, AP started");
    }
  } else {
    wf.runAP();
  }

  createWebServer();
}

void loop() {
  server.handleClient();

  if (wf.connectionStatus == true) {
    int feed = firebaseDB.getFeed();

    if (feed == 1) {
      cfServo.feed();
      Serial.println("Cat has been fed");
      firebaseDB.disableFeed();
    }

    delay(5000);
  }
}

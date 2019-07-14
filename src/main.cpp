#include <Arduino.h>
#include <CFWiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FBDB.h>
#include <RBD_Timer.h>
#include <Servo.h>
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
Servo servoEngine;
int servoEnginePin = 5;
int loopSensorPin = 4;
RBD::Timer firebaseTimer(5000);
RBD::Timer loopTimer(1350);
int feed = 0;

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
      Serial.println("WiFi connected");

      Serial.println("Firebase has been configured");
      firebaseDB.begin();

      servoEngine.attach(servoEnginePin);
      Serial.println("Servo has been configured");
    } else {
      storage.clear();
      wf.runAP();
      Serial.println("Storage was cleared, AP started");
    }
  } else {
    wf.runAP();
    Serial.println("AP started");
  }

  createWebServer();
  firebaseTimer.restart();
  loopTimer.restart();
}

void loop() {
  server.handleClient();

  // get data from firebase
  if (firebaseTimer.isExpired()) {
    if (wf.connectionStatus == true) {
      feed = firebaseDB.getFeed();

      if (feed == 1) {
        loopTimer.restart();

        Serial.println("Servo has been run");
        servoEngine.write(0);
      }
    }

    firebaseTimer.restart();
  }

  int buttonState = digitalRead(loopSensorPin);

  if (buttonState == HIGH && feed == 1) {
    servoEngine.write(90);
    feed = 0;
    Serial.println("Terminate loop by sensor");

    firebaseDB.disableFeed();
  }

  if (loopTimer.isExpired() && feed == 1) {
    feed = 0;
    servoEngine.write(90);
    Serial.println("Terminate loop timer");

    firebaseDB.disableFeed();
  }

  // if (buttonState == HIGH || loopTimer.isExpired()) {
  //   servoEngine.write(90);
  //   Serial.println("Terminate loop by sensor or loop timer");
  //
  //   firebaseDB.disableFeed();
  //   Serial.println("Cat has been fed");
  // }
}

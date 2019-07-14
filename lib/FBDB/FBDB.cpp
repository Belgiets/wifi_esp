#include "FBDB.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>

FBDB::FBDB(String firebaseHost, String path) {
  _firebaseHost = firebaseHost;
  _path = path;
};

void FBDB::begin(void) {
  Firebase.begin(_firebaseHost);
  Serial.println("Firebase started");
};

int FBDB::getFeed(void) {
  int feed = Firebase.getInt(_path);

  if (Firebase.failed()) {
    Serial.println("Getting data failed");
    feed = 0;
  }

  return feed;
};

void FBDB::disableFeed(void) { Firebase.setInt(_path, 0); };

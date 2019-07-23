#include "FBDB.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>

FBDB::FBDB(String firebaseHost, String actionPath) {
  _firebaseHost = firebaseHost;
  _path = actionPath;
  _statusPath = actionPath + "/status";
  _updatedPath = actionPath + "/updated";
};

void FBDB::begin(void) {
  Firebase.begin(_firebaseHost);
  Serial.println("Firebase started");
};

int FBDB::getFeed(void) {
  int feed = Firebase.getInt(_statusPath);

  if (Firebase.failed()) {
    Serial.println("Getting data failed");
    feed = 0;
  }

  return feed;
};

void FBDB::disableFeed(void) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject &feedObject = jsonBuffer.createObject();
  //JsonObject &timestamp = feedObject.createNestedObject("updated");
  feedObject["status"] = 0;
  feedObject["updated"] = "timestamp";

  Firebase.push(_path, feedObject);

  // Firebase.setInt(_statusPath, 0);
  // Firebase.setString(_updatedPath, serverTimestamp);
};

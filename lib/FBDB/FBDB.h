#ifndef FBDB_h
#define FBDB_h

#include <Arduino.h>
#include <FirebaseArduino.h>

class FBDB {
private:
  String _firebaseHost;
  String _path;
  String _statusPath;
  String _updatedPath;

public:
  FBDB(String firebaseHost, String _path);
  void begin(void);
  int getFeed();
  void disableFeed(void);
};

#endif

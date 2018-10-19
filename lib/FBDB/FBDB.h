#ifndef FBDB_h
#define FBDB_h

#include <Arduino.h>
#include <FirebaseArduino.h>

class FBDB {
private:
  String _firebaseHost;
  String _path;

public:
  FBDB(String firebaseHost, String _path);
  void begin(void);
  int getFeed();
  void disableFeed(void);
};

#endif

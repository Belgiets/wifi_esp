#ifndef CFServo_h
#define CFServo_h

#include <Arduino.h>
#include <Servo.h>

class CFServo {
private:
  int _servoPin;
  Servo myServo;

public:
  CFServo(int servoPin);
  void setup(void);
  void feed(void);
};

#endif

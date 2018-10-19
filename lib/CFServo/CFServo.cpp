#include "CFServo.h";

CFServo::CFServo(int servoPin) { _servoPin = servoPin; };

void CFServo::setup(void) {
  myServo.attach(_servoPin);
  Serial.println("Servo has been configured");
};

void CFServo::feed(void) {
  myServo.write(0);
  delay(2000);
  myServo.write(90);
  delay(2000);
};

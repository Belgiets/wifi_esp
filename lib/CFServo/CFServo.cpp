#include "CFServo.h";
#include <Arduino.h>
#include <Servo.h>

CFServo::CFServo(int servoPin) { _servoPin = servoPin; };

void CFServo::setup(void) {
  myServo.attach(_servoPin);
  Serial.println("Servo has been configured");
};

void CFServo::feed(void) {
  Serial.println("run");
  myServo.write(0);
  delay(1350);

  Serial.println("stop");
  myServo.write(90);
  //
  // Serial.println("180 deg");
  // myServo.write(180);
  // delay(2000);
};

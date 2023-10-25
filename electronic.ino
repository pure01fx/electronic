#include "QGPMaker_IICSensorbar.h"
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield motorShield = new QGPMaker_MotorShield();
QGPMaker_Servo *servo1 = motorShield.getServo(1);

void setup() {
  // put your setup code here, to run once:
  motorShield.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  servo1->writeServo(10);
  delay(1000);
  servo1->writeServo(120);
  delay(1000);
}

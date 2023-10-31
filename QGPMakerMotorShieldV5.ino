/*!
 * MindPlus
 * uno
 *
 */

#if false
#include <Wire.h>
#include "PS2X_lib.h"
#include "QGPMaker_MotorShield.h"
#include "Adafruit_MS_PWMServoDriver.h"

PS2X                  ps2x;
QGPMaker_MotorShield  AFMS = QGPMaker_MotorShield();
QGPMaker_DCMotor      *DCMotor_1 = AFMS.getMotor(1);

void setup() {
	Serial.begin(9600);
	Serial.println("********");
	
	int error = 0;
	do{
	  error = ps2x.config_gamepad(13,11,10,12, true, true);
	  
	Serial.println(error);
	if(error == 0){break;}else{delay(100);}}while(1); for(size_t i = 0; i < 50; i++){ ps2x.read_gamepad(false, 0);delay(10);}
	AFMS.begin(50);
	Serial.println("hello");
}
void loop() {
  ps2x.read_gamepad(false, 0);
	DCMotor_1->setSpeed(200);
	DCMotor_1->run(FORWARD);
	if (ps2x.Button(PSB_PAD_UP)) {
		Serial.println("1111111");
	}
  delay(10);
}

#endif

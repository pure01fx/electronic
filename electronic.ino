#include <Wire.h>
#include <Adafruit_GFX.h>      // install Adafruit GFX and Adafruit SSD1306
#include <Adafruit_SSD1306.h>
#include "QGPMaker_IICSensorbar.h"
#include "QGPMaker_MotorShield.h"
#include "PS2X_lib.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// QGPMaker_MotorShield motorShield = new QGPMaker_MotorShield();
// QGPMaker_Servo *servo1 = motorShield.getServo(1);

PS2X ps2x;  // create PS2 Controller Class

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);  //开像素点发光
  display.clearDisplay();       //清屏

  display.setTextSize(1);    //设置字体大小
  display.setCursor(35, 5);  //设置显示位置
  display.println("----------");

  display.setTextSize(2);     //设置字体大小
  display.setCursor(15, 30);  //设置显示位置
  display.println("OLED TEST");

  display.display();  // 开显示
  Serial.begin(115200);
  // motorShield.begin();

  while (!Serial.availableForWrite()) {
    delay(100);
  }
  Serial.println("Serial ready");
  int error = ps2x.config_gamepad(13, 11, 10, 12, true, true);  //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  #if false
  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to [url]www.billporter.info[/url] for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit [url]www.billporter.info[/url] for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit [url]www.billporter.info[/url] for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  #endif
  Serial.print(ps2x.Analog(1), HEX);


  byte type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}

int state = 0;

void loop() {
  // put your main code here, to run repeatedly:
  // servo1->writeServo(10);
  // delay(1000);
  // servo1->writeServo(120);
  // delay(1000);
  display.clearDisplay();       //清屏

  display.setTextSize(1);    //设置字体大小
  display.setCursor(35, 5);  //设置显示位置
  if (state == 0) display.println("----------");

  display.setTextSize(2);     //设置字体大小
  display.setCursor(15, 30);  //设置显示位置
  display.println("OLED TEST");

  display.display();  // 开显示

  state = state ^ 1;

  delay(500);
}

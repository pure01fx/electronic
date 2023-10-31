#include <Wire.h>
#include <Adafruit_GFX.h>  // install Adafruit GFX and Adafruit SSD1306
#include <Adafruit_SSD1306.h>
#include "QGPMaker_IICSensorbar.h"
#include "QGPMaker_MotorShield.h"
#include "PS2X_lib.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// QGPMaker_MotorShield motorShield = new QGPMaker_MotorShield();
// QGPMaker_Servo *servo1 = motorShield.getServo(1);

PS2X ps2x;  // create PS2 Controller Class

const char* button_name = "INIT";
char stick_left[128];
char stick_right[128];

void setup() {
  stick_left[0] = 0;
  stick_right[0] = 0;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);  //开像素点发光
  display.clearDisplay();       //清屏

  display.setTextSize(2);    //设置字体大小
  display.setCursor(0, 0);  //设置显示位置
  display.println("@pure01fx");
  display.println("OLED TEST");

  display.display();  // 开显示

  delay(1000);

  Serial.begin(115200);
  // motorShield.begin();

  while (!Serial.availableForWrite()) {
    delay(100);
  }

  Serial.println("Serial ready");

  while (true) {
    int error = ps2x.config_gamepad(13, 11, 10, 12, false, false);  //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    // Serial.println(error);
    if (error == 0) {
      break;
    }
    delay(1000);
  }
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

  // byte type = ps2x.readType();
  // switch (type) {
  //   case 1:
  //     Serial.println("DualShock Controller Found");
  //     break;
  //   default:
  //     Serial.println("Unknown Controller type");
  //     break;
  // }
}

void oled_step() {
  display.clearDisplay();  //清屏

  display.setTextSize(2);    //设置字体大小
  display.setCursor(0, 5);  //设置显示位置
  display.println(button_name);

  // display.setTextSize(2);     //设置字体大小
  // display.setCursor(15, 30);  //设置显示位置
  // display.println(stick_left);
  // display.println(stick_right);

  display.display();  // 开显示
}

void ps2x_get_name() {
  // print('\n'.join([f'  if(ps2x.Button({x[0]})) button_name = "{x[0]}";' for x in [(x[0], x[1]) for x in [x[8:].split() for x in s.split('\n')[1:-1]]]]))
  button_name = "NULL";
  if(ps2x.Button(PSB_SELECT)) button_name = "SELECT";
  if(ps2x.Button(PSB_L3)) button_name = "L3";
  if(ps2x.Button(PSB_R3)) button_name = "R3";
  if(ps2x.Button(PSB_START)) button_name = "START";
  if(ps2x.Button(PSB_PAD_UP)) button_name = "PAD_UP";
  if(ps2x.Button(PSB_PAD_RIGHT)) button_name = "PAD_RIGHT";
  if(ps2x.Button(PSB_PAD_DOWN)) button_name = "PAD_DOWN";
  if(ps2x.Button(PSB_PAD_LEFT)) button_name = "PAD_LEFT";
  if(ps2x.Button(PSB_L2)) button_name = "L2";
  if(ps2x.Button(PSB_R2)) button_name = "R2";
  if(ps2x.Button(PSB_L1)) button_name = "L1";
  if(ps2x.Button(PSB_R1)) button_name = "R1";
  if(ps2x.Button(PSB_GREEN)) button_name = "GREEN";
  if(ps2x.Button(PSB_RED)) button_name = "RED";
  if(ps2x.Button(PSB_BLUE)) button_name = "BLUE";
  if(ps2x.Button(PSB_PINK)) button_name = "PINK";
  if(ps2x.Button(PSB_TRIANGLE)) button_name = "TRIANGLE";
  if(ps2x.Button(PSB_CIRCLE)) button_name = "CIRCLE";
  if(ps2x.Button(PSB_CROSS)) button_name = "CROSS";
  if(ps2x.Button(PSB_SQUARE)) button_name = "SQUARE";
}

void ps2x_get_pos() {
  int lx = ps2x.Analog(PSS_LX);
  int ly = ps2x.Analog(PSS_LY);
  int rx = ps2x.Analog(PSS_RX);
  int ry = ps2x.Analog(PSS_RY);
  sprintf(stick_left,  "L: (%d, %d)", lx, ly);
  sprintf(stick_right, "R: (%d, %d)", rx, ry);
  //Serial.println((stick_left));
  //Serial.println((stick_right));
}

void ps2x_step() {
  ps2x.read_gamepad();
  ps2x_get_name();
  // Serial.println((button_name));
  // ps2x_get_pos();
}

void loop() {
  // put your main code here, to run repeatedly:
  // servo1->writeServo(10);
  // delay(1000);
  // servo1->writeServo(120);
  // delay(1000);
  ps2x_step();
  oled_step();
  delay(100);
}

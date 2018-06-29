#include <M5Stack.h>
#include <QTRSensors.h>
#include <BamBotMotorDriver.h>
#include "Adafruit_MCP23008.h"

#define INCREMENT 10  //used to increment drive speed based on button presses
#define START_SPEED 200
#define LINE_PIN1 18
#define LINE_PIN2 19
#define LINE_PIN3 23

//SET STARTING PID VALUES//
float kp = 0.4;
float kd = 3.5;

int motor1Speed, motor2Speed;
float lastError = 0;
int baseMotorSpeed = START_SPEED;
bool tuneMode = false;      //false for tuning kp and true for tuning kd

//Create an object for your line sensor
//uses pins 18, 19, 23 meaning this sketch is incompatible with using the SD
//card or any other SPI device
QTRSensorsRC qtr((unsigned char[]) {LINE_PIN1, LINE_PIN2, LINE_PIN3), 3);

//Create the motor objects
BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

void setup() {
  M5.begin();

  mcp.begin();
  motors.init(mcp);

  M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Press A to calibrate...");
  while (!M5.BtnA.wasPressed()) {
    M5.update();
  }
  for (int i=0; i<140; i++) {
    qtr.calibrate();
    delay(20);
  }

  M5.Lcd.fillScreen(0x0000);
  M5.Lcd.setCursor(14, 14, 2); M5.print("Place on track");
  M5.Lcd.setCursor(14, 70, 3); M5.print("Press A to Go!");
  while(!M5.BtnA.wasPressed()) {
    M5.update();
  }
}

void loop() {
  ////SET MOTOR SPEEDS////
  motors.setSpeeds(motor1Speed, motor2Speed);

  ////PID LOOP////
  unsigned int sensors[3];
  int position = qtr.readLine(sensors); //returns a value between 0 and 2000... 1000 is center point

  float error = (float)position - 1000.0;

  int driveCorrection = kp*error + kd*(error - lastError);
  lastError = error;

  motor1Speed = baseMotorSpeed + driveCorrection;
  motor2Speed = baseMotorSpeed - driveCorrection;

  motor1Speed = constrain(baseMotorSpeed, 0, MAX_SPEED);
  motor2Speed = constrain(baseMotorSpeed, 0, MAX_SPEED);

  ////ADJUST GAIN USING BUTTONS////
  if (M5.BtnA.wasPressed()) {
    tuneMode = 1;
    M5.Lcd.fillScreen(0x0000);
    M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Tune P Gain (Kp)");
    M5.Lcd.setCursor(14, 35, 2); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55, 2); M5.Lcd.print("B to raise Kp");
    M5.Lcd.setCursor(14, 75, 2); M5.Lcd.print("C to lower Kp");
  }
}


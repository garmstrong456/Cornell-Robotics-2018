#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

const int BASE_SPEED = 200;
const int MIN_SPEED = 0;
const int MAX_SPEED = 400;

int kp = 2, kd = 0;
int error = 0, lastError = 0;
int speedCorrection;
int m1Speed, m2Speed;
bool usePID = true;


void setup() {
  M5.begin();

  mcp.begin();
  motors.init(mcp);
  motors.attachEncoders(2,5,16,17);

}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    usePID = !usePID;
  }

  if (usePID) {
  
    error = motors.motor2Position() - motors.motor1Position();
    speedCorrection = kp*error + kd*(error - lastError);
    lastError = error;
  
    m1Speed = constrain(BASE_SPEED + speedCorrection, MIN_SPEED, MAX_SPEED);
    m2Speed = constrain(BASE_SPEED - speedCorrection, MIN_SPEED, MAX_SPEED);
  }
  else {
    m1Speed = BASE_SPEED;
    m2Speed = BASE_SPEED;
  }
  
  motors.setSpeeds(m1Speed, m2Speed);

  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print(error); M5.Lcd.print("         ");
  M5.Lcd.setCursor(0,15,2); M5.Lcd.print(speedCorrection); M5.Lcd.print("         ");
  M5.Lcd.setCursor(0,30,2); M5.Lcd.print(m1Speed); M5.Lcd.print("      ");
  M5.Lcd.setCursor(0,45,2); M5.Lcd.print(m2Speed); M5.Lcd.print("      ");

}

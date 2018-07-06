/*
 * drive_straight_encoders
 * 
 * Greg Armstrong July 2018
 * 
 * Use the encoders to drive in a perfectly straight line
 * 
 * This sketch measures the rotation from the onboard encoders and will use PID control
 * to adjust motor speed in order to keep them equal
 * 
 * Pressing the "A" button will toggle the PID control on and off
 * When PID is off both motors will be set to the base speed
 * 
 * Integral control is not implemented
 */

#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

//****************************************
//Adjust these values to tune the PID loop
//****************************************

//BASE_SPEED is the average speed the robot will drive
//MIN_SPEED and MAX_SPEED are the maximum and minimum correction allowed
const int BASE_SPEED = 200;
const int MIN_SPEED = 0;
const int MAX_SPEED = 400;

//PID gains
int kp = 2, kd = 0;

//****************************************

int err = 0, lastError = 0;
int speedCorrection;
int m1Speed, m2Speed;
bool usePID = true;


void setup() {
  //always put this first to avoid problems
  M5.begin();

  //Initialize the motors and encoders
  mcp.begin();
  motors.init(mcp);
  motors.attachEncoders(2,5,16,17);
}

void loop() {
  M5.update();

  //Toggle PID if the button was pressed
  if (M5.BtnA.wasPressed()) {
    usePID = !usePID;
  }

  //PID controll
  if (usePID) {
  
    err = motors.motor2Position() - motors.motor1Position();
    speedCorrection = kp*err + kd*(err - lastError);
    lastError = err;

    //Keep the speeds within the user defined limits
    m1Speed = constrain(BASE_SPEED + speedCorrection, MIN_SPEED, MAX_SPEED);
    m2Speed = constrain(BASE_SPEED - speedCorrection, MIN_SPEED, MAX_SPEED);
  }
  else {    //No PID controll
    m1Speed = BASE_SPEED;
    m2Speed = BASE_SPEED;
  }

  //Set the motor speeds
  motors.setSpeeds(m1Speed, m2Speed);

  M5.Lcd.setCursor(0, 0,2); M5.Lcd.printf("error: %6d   ", err);
  M5.Lcd.setCursor(0,15,2); M5.Lcd.printf("speed correction: %6d   ", speedCorrection);
  M5.Lcd.setCursor(0,30,2); M5.Lcd.printf("motor speeds: %6d  %6d   ", m1Speed, m2Speed);
  M5.Lcd.setCursor(0,45,2); M5.Lcd.printf("encoder values: %6d  %6d   ", motors.motor1Position() - motors.motor2Position());

}

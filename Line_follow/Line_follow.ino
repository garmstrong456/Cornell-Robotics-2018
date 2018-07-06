#include <M5Stack.h>
#include <QTRSensors.h>
#include <BamBotMotorDriver.h>
#include "Adafruit_MCP23008.h"

//SET STARTING PID VALUES//
float kp = 0.4;
float kd = 3.5;
int baseMotorSpeed = 200;
const int MAX_SPEED = 400;

//SET ADJUSTMENT INCREMENTS//
float kpInc = 0.1;
float kdInc = 0.1;
int speedInc = 10;

int motor1Speed, motor2Speed;
float lastError = 0;

//Create an object for your line sensor
//uses pins 18, 19, 23 meaning this sketch is incompatible with using the SD
//card or any other SPI device
QTRSensorsRC qtr((unsigned char[]) {16, 17, 2}, 3);

//Create the motor objects
BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

void setup() {
  M5.begin(true, false);    //initialize the M5 with the SD card disabled

  mcp.begin();
  motors.init(mcp);

  M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Press A to calibrate...");
  while (!M5.BtnA.wasPressed()) {
    M5.update();
  }
  M5.Lcd.clear();
  M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Calibrating...");
  M5.Lcd.setCursor(14, 29, 2); M5.Lcd.print("move sensor back and forth over line");
  for (int i=0; i<140; i++) {
    qtr.calibrate();
    delay(20);
  }

  M5.update();
  M5.Lcd.clear();
  M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Place on track");
  M5.Lcd.setCursor(14, 70, 2); M5.Lcd.print("Press A to Go!");
  while(!M5.BtnA.wasPressed()) {
    M5.update();
  }
  M5.Lcd.clear();
}

void loop() {
  M5.update();
  
  //set motor speeds
  motors.setSpeeds(motor1Speed, motor2Speed);

  ////////////////
  ////PID LOOP////
  ////////////////

  //update the position
  unsigned int sensors[3];
  int position = qtr.readLine(sensors); //returns a value between 0 and 2000... 1000 is center point

  //calculate the error
  float error = (float)position - 1000.0;

  //calculate the correction
  int driveCorrection = kp*error + kd*(error - lastError);
  lastError = error;

  //calculate the new motor speeds
  motor1Speed = baseMotorSpeed + driveCorrection;
  motor2Speed = baseMotorSpeed - driveCorrection;

  //keep the motor speeds within defined limits (0..MAX_SPEED)
  motor1Speed = constrain(motor1Speed, 0, MAX_SPEED);
  motor2Speed = constrain(motor2Speed, 0, MAX_SPEED);

  ////////////////////
  ////END PID LOOP////
  ////////////////////

  //Update display
  M5.Lcd.setCursor(0,  0, 2); M5.Lcd.printf("Motor 1 Speed:    %4d", motor1Speed);
  M5.Lcd.setCursor(0, 15, 2); M5.Lcd.printf("Motor 2 Speed:    %4d", motor2Speed);
  M5.Lcd.setCursor(0, 30, 2); M5.Lcd.printf("Error:            %4d", position);
  M5.Lcd.setCursor(0, 45, 2); M5.Lcd.printf("Drive Correction: %4d", driveCorrection);
  M5.Lcd.setCursor(0, 60, 2); M5.Lcd.printf("kp: %2.2f,  kd: %2.2f,  base speed %d", kp, kd, baseMotorSpeed);
  M5.Lcd.setCursor(0, 90, 2); M5.Lcd.print("Button Menu");
  M5.Lcd.setCursor(0, 105, 2); M5.Lcd.print("A: adjust kp  B: adjust kd  C: adjust speed");  

  ////ADJUST GAIN USING BUTTONS////

  //Button A = adjust kp
  if (M5.BtnA.wasPressed()) {
    M5.update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Tune P Gain (Kp)");
    M5.Lcd.setCursor(14, 35, 2); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55, 2); M5.Lcd.print("B to raise Kp");
    M5.Lcd.setCursor(14, 75, 2); M5.Lcd.print("C to lower Kp");

    while (!M5.BtnA.wasPressed()) {
      M5.update();
      if (M5.BtnB.wasPressed()) {
        kp = kp + kpInc;
      }
      if (M5.BtnC.wasPressed()) {
        kp = kp - kpInc;
      }
      if (kp < 0) kp = 0;
      M5.Lcd.setCursor(14, 95, 2); M5.Lcd.printf("Current Kp: %3.2f", kp);
    }
    M5.Lcd.clear();
  }

  //Button B = adjust kd
  if (M5.BtnB.wasPressed()) {
    M5.update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Tune D Gain (Kd)");
    M5.Lcd.setCursor(14, 35, 2); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55, 2); M5.Lcd.print("B to raise Kd");
    M5.Lcd.setCursor(14, 75, 2); M5.Lcd.print("C to lower Kd");
    
    while (!M5.BtnA.wasPressed()) {
      M5.update();
      if (M5.BtnB.wasPressed()) {
        kd += kdInc;
      }
      if (M5.BtnC.wasPressed()) {
        kd -= kdInc;
      }
      if (kd < 0) kd = 0;
      M5.Lcd.setCursor(14, 95, 2); M5.Lcd.printf("Current Kd: %3.2f", kd);
    }
    M5.Lcd.clear();
  }

  //Button C = adjust base speed
  if (M5.BtnC.wasPressed()) {
    M5.update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(14, 14, 2); M5.Lcd.print("Adjust base speed");
    M5.Lcd.setCursor(14, 35, 2); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55, 2); M5.Lcd.print("B to go faster");
    M5.Lcd.setCursor(14, 75, 2); M5.Lcd.print("C to go slower");
    
    while (!M5.BtnA.wasPressed()) {
      M5.update();
      if (M5.BtnB.wasPressed()) {
        baseMotorSpeed += speedInc;
      }
      if (M5.BtnC.wasPressed()) {
        baseMotorSpeed -= speedInc;
      }
      baseMotorSpeed = constrain(baseMotorSpeed, 0, MAX_SPEED);
      M5.Lcd.setCursor(14, 95, 2); M5.Lcd.printf("Current speed: %3d", baseMotorSpeed);
    }
    M5.Lcd.clear();
  }
}


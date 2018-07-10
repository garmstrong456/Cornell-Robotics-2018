#include "M5Stack.h"
#include "utility/MPU9250.h"
#include "BamBotMotorDriver.h"
#include "Adafruit_MCP23008.h"
#include <BambotAHRS.h>
#include <Wire.h>

Mahony AHRSfilter;
MPU9250 IMU;
BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

void setup() {
  M5.begin();
  Wire.begin();

  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();

  motors.init(mcp);

  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print("Press A button to turn 90deg");
}

uint16_t totalTime = 0, lastTime = 0;
bool turning = false;
int targetHeading, currentHeading;

void loop() {
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {
    readAndScaleIMU();

    totalTime = micros() - lastTime;
    lastTime = micros();

    AHRSfilter.updateIMU(IMU.gx, IMU.gy, IMU.gz, IMU.ax, IMU.ay, IMU.az, totalTime);
    currentHeading = (int)(AHRSfilter.getYaw()*RAD_TO_DEG) + 180;
  }

  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print("Press A button to turn 90deg");
  M5.Lcd.setCursor(0,15,2); M5.Lcd.print("Heading: ");
  M5.Lcd.setCursor(60,15,2); M5.Lcd.print(currentHeading); M5.Lcd.print("     ");

  if (M5.BtnA.wasPressed()) {
    targetHeading = (currentHeading + 90) % 360;
    if (targetHeading == 0) {targetHeading = 1;}
    turning = true;
  }

  if (turning) {
    M5.Lcd.setCursor(0,30,2); M5.Lcd.print("Turning to: ");
    M5.Lcd.setCursor(80,30,2); M5.Lcd.print(targetHeading);
    if (abs(currentHeading - targetHeading) < 1) {
        motors.setSpeeds(0,0);
        turning = false;
        M5.Lcd.clear();
    } else {
        motors.setSpeeds(200, -200);
    }
  }

  M5.update();
}

void readAndScaleIMU() {
  IMU.readAccelData(IMU.accelCount);
  IMU.getAres();
  IMU.ax = IMU.accelCount[0];
  IMU.ay = IMU.accelCount[1];
  IMU.az = IMU.accelCount[2];

  IMU.readGyroData(IMU.gyroCount);
  IMU.getGres();
  IMU.gx = (float)IMU.gyroCount[0]*IMU.gRes*DEG_TO_RAD;
  IMU.gy = (float)IMU.gyroCount[1]*IMU.gRes*DEG_TO_RAD;
  IMU.gz = (float)IMU.gyroCount[2]*IMU.gRes*DEG_TO_RAD;
}

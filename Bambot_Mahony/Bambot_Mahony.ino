/*
 * Bambot_Mahony
 * 
 * Greg Armstrong July 2018
 * 
 * This sketch demonstrates orientation tracking using the Mahony AHRS algorithm
 * 
 * In order to work properly the robot must be placed on a level surface and be
 * as still as possible while it starts up.
 * 
 */

#include <M5Stack.h>
#include "utility/MPU9250.h"
#include <BambotAHRS.h>
#include <Wire.h>

Mahony AHRSfilter;
MPU9250 IMU;

void setup() {
  M5.begin();   //initialize the M5
  Wire.begin(); //Start I2C communication

  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();

  //Set up the LCD to display pitch, yaw, roll and time between readings
  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print("P: ");
  M5.Lcd.setCursor(0,15,2); M5.Lcd.print("Y: ");
  M5.Lcd.setCursor(0,30,2); M5.Lcd.print("R: ");
  M5.Lcd.setCursor(0,45,2); M5.Lcd.print("T: ");
}

uint32_t prevTime;  //time of the last reading in milliseconds
float deltaT;       //time between readings in seconds

void loop() {
  //check to see if new data is available
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {
    readAndScaleIMU();

    //record the elapsed time since the last reading
    deltaT = (float)(micros() - prevTime)/1000000.0;
    prevTime = micros();

    //update the orientation vector
    AHRSfilter.updateIMU(IMU.gx, IMU.gy, IMU.gz, IMU.ax, IMU.ay, IMU.az, deltaT);
  }

  //display the data
  M5.Lcd.setCursor(15, 0,2); M5.Lcd.print(AHRSfilter.getPitch()); M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,15,2); M5.Lcd.print(AHRSfilter.getYaw());   M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,30,2); M5.Lcd.print(AHRSfilter.getRoll());  M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,45,2); M5.Lcd.print(deltaT); M5.Lcd.print("       ");
}


//Reads data from the MPU
//Apply user bias corrections to the mag data
void readAndScaleIMU() {
  IMU.readAccelData(IMU.accelCount);
  IMU.getAres();
  IMU.ax = IMU.accelCount[0];
  IMU.ay = IMU.accelCount[1];
  IMU.az = IMU.accelCount[2];

  IMU.readGyroData(IMU.gyroCount);
  IMU.getGres();

  IMU.gx = (float)IMU.gyroCount[0]*IMU.gRes;
  IMU.gy = (float)IMU.gyroCount[1]*IMU.gRes;
  IMU.gz = (float)IMU.gyroCount[2]*IMU.gRes;

  IMU.readMagData(IMU.magCount);
  IMU.getMres();
  IMU.mx = (float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - IMU.magbias[0];
  IMU.my = (float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - IMU.magbias[1];
  IMU.mz = (float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - IMU.magbias[2];
}

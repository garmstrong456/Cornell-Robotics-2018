#include "M5Stack.h"
#include "utility/MPU9250.h"
#include <GregMahony.h>
#include <Wire.h>

GregMahony AHRSfilter;
MPU9250 IMU;

//Soft Iron corrections
float magScale_x = 1.093;
float magScale_y = 1.032;
float magScale_z = 0.896;

void setup() {
  M5.begin();
  Wire.begin();

  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
  IMU.initAK8963(IMU.magCalibration);

  //Hard Iron corrections
  IMU.magbias[0] = -9532.0;
  IMU.magbias[1] =  4362.0;
  IMU.magbias[2] = -8248.0;

  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print("P: ");
  M5.Lcd.setCursor(0,15,2); M5.Lcd.print("Y: ");
  M5.Lcd.setCursor(0,30,2); M5.Lcd.print("R: ");
  M5.Lcd.setCursor(0,45,2); M5.Lcd.print("T: ");
}

uint16_t totalTime = 0, lastTime = 0;

void loop() {
  uint16_t readTime;
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {
    readAndScaleIMU();

    totalTime = micros() - lastTime;
    lastTime = micros();
    
    AHRSfilter.update(IMU.gx, IMU.gy, IMU.gz, IMU.ax, IMU.ay, IMU.az, IMU.mx, IMU.my, IMU.mz, totalTime);
  }

  M5.Lcd.setCursor(15, 0,2); M5.Lcd.print(AHRSfilter.getPitch()*RAD_TO_DEG); M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,15,2); M5.Lcd.print(AHRSfilter.getYaw()*RAD_TO_DEG);   M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,30,2); M5.Lcd.print(AHRSfilter.getRoll()*RAD_TO_DEG);  M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,45,2); M5.Lcd.print(totalTime);
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

  IMU.readMagData(IMU.magCount);
  IMU.getMres();
  IMU.mx = magScale_x*((float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - IMU.magbias[0]);
  IMU.my = magScale_y*((float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - IMU.magbias[1]);
  IMU.mz = magScale_z*((float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - IMU.magbias[2]);
}

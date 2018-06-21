#include <M5Stack.h>
#include "utility/MPU9250.h"
#include <MahonyAHRS.h>
#include <Wire.h>

Mahony AHRSfilter;
MPU9250 IMU;

const int magBiasX = 470;
const int magBiasY = 120;
const int magBiasZ = 125;

void setup() {
  M5.begin();
  Wire.begin();

  byte c = IMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print("MPU9250 Address");
  M5.Lcd.setCursor(0,15,2); M5.Lcd.print(c, HEX);
  delay(1000);

  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
  IMU.initAK8963(IMU.magCalibration);

  M5.Lcd.setCursor(0, 0,2); M5.Lcd.print("P: ");
  M5.Lcd.setCursor(0,15,2); M5.Lcd.print("Y: ");
  M5.Lcd.setCursor(0,30,2); M5.Lcd.print("R: ");
  M5.Lcd.setCursor(0,45,2); M5.Lcd.print("T: ");
}

void loop() {
  uint16_t readTime;
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {
    readTime = millis();
    readAndScaleIMU();
    readTime = millis() - readTime;

    AHRSfilter.updateIMU(IMU.gx, IMU.gy, IMU.gz, IMU.ax, IMU.ay, IMU.az);
    //AHRSfilter.update(IMU.gx, IMU.gy, IMU.gz, IMU.ax, IMU.ay, IMU.az, IMU.mx, IMU.my, IMU.mz);
  }

  M5.Lcd.setCursor(15, 0,2); M5.Lcd.print(AHRSfilter.getPitch()*RAD_TO_DEG); M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,15,2); M5.Lcd.print(AHRSfilter.getYaw()*RAD_TO_DEG);   M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,30,2); M5.Lcd.print(AHRSfilter.getRoll()*RAD_TO_DEG);  M5.Lcd.print("    ");
  M5.Lcd.setCursor(15,45,2); M5.Lcd.print(readTime);
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
  IMU.mx = (float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - magBiasX;
  IMU.my = (float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - magBiasY;
  IMU.mz = (float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - magBiasZ;
}

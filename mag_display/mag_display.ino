#include <M5Stack.h>
#include "utility/MPU9250.h"
#include "utility/quaternionFilters.h"


MPU9250 IMU;
float scaleX = 1.093, scaleY = 1.359, scaleZ = 0.741;

void setup(){
  
  M5.begin();
  Wire.begin();
  
  IMU.MPU9250SelfTest(IMU.SelfTest);
  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
  IMU.initAK8963(IMU.magCalibration);

  IMU.magbias[0] = -10617; IMU.magbias[1] = 6939; IMU.magbias[2] = -11192;

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(GREEN ,BLACK);
  M5.Lcd.fillScreen(BLACK);
}

void updateIMU() {
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {
    
    //Read and scale the acc data
    IMU.readAccelData(IMU.accelCount);
    IMU.getAres();
    IMU.ax = (float)IMU.accelCount[0]*IMU.aRes;
    IMU.ay = (float)IMU.accelCount[1]*IMU.aRes;
    IMU.az = (float)IMU.accelCount[2]*IMU.aRes;

    //Read and scale the gyro data
    IMU.readGyroData(IMU.gyroCount);
    IMU.getGres();
    IMU.gx = (float)IMU.gyroCount[0]*IMU.gRes;
    IMU.gy = (float)IMU.gyroCount[1]*IMU.gRes;
    IMU.gz = (float)IMU.gyroCount[2]*IMU.gRes;

    //Read and scale the mag data
    IMU.readMagData(IMU.magCount);
    IMU.getMres();
    IMU.mx = ((float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - IMU.magbias[0])*scaleX;
    IMU.my = ((float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - IMU.magbias[1])*scaleY;
    IMU.mz = ((float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - IMU.magbias[2])*scaleZ;
  }
}

void updatePitchYawRoll() {
  IMU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ() *
                *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1) * *(getQ()+1)
                - *(getQ()+2) * *(getQ()+2) - *(getQ()+3) * *(getQ()+3));
  IMU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ() *
                *(getQ()+2)));
  IMU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2) *
                *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1) * *(getQ()+1)
                - *(getQ()+2) * *(getQ()+2) + *(getQ()+3) * *(getQ()+3));
  IMU.pitch *= RAD_TO_DEG;
  IMU.yaw   *= RAD_TO_DEG;
  // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
  //   8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
  // - http://www.ngdc.noaa.gov/geomag-web/#declination
  IMU.yaw   -= 8.5;
  IMU.roll  *= RAD_TO_DEG;
}

void loop()
{
  updateIMU();

  // Serial print and/or display at 0.5 s rate independent of data rates
  IMU.delt_t = millis() - IMU.count;

  // update LCD once per tenth-second independent of read rate
  // if (IMU.delt_t > 500)
  if (IMU.delt_t > 100)
  {
    
    // M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextFont(2);

    M5.Lcd.setCursor(0, 0); M5.Lcd.print("     x       y       z ");
    M5.Lcd.setCursor(0,  24);
    M5.Lcd.printf("% 6d  % 6d  % 6d     mg   \r\n",  (int)(1000*IMU.ax), (int)(1000*IMU.ay), (int)(1000*IMU.az));
    M5.Lcd.setCursor(0,  44);
    M5.Lcd.printf("% 6d  % 6d  % 6d      o/s  \r\n", (int)(IMU.gx), (int)(IMU.gy), (int)(IMU.gz));
    M5.Lcd.setCursor(0,  64);
    M5.Lcd.printf("% 6d  % 6d  % 6d     mG    \r\n",  (int)(IMU.mx), (int)(IMU.my), (int)(IMU.mz));

    M5.Lcd.setCursor(12, 144); 
    M5.Lcd.print("rt: ");
    M5.Lcd.print((float) IMU.sumCount / IMU.sum, 2);
    M5.Lcd.print(" Hz    ");

    IMU.count = millis();
    IMU.sumCount = 0;

  } // if (IMU.delt_t > 500)
}

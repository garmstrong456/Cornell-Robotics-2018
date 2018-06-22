#include <M5Stack.h>
#include "utility/MPU9250.h"
#include "utility/quaternionFilters.h"


MPU9250 IMU;
float maxx = -10.0E10, minx = 10.0E10;
float maxy = -10.0E10, miny = 10.0E10;
float maxz = -10.0E10, minz = 10.0E10;
float scalex, scaley, scalez;
float biasx, biasy, biasz;

void setup(){
  
  M5.begin();
  Wire.begin();
  
  IMU.MPU9250SelfTest(IMU.SelfTest);
  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
  IMU.initAK8963(IMU.magCalibration);

  IMU.magbias[0] = 0.0; IMU.magbias[1] = 0.0; IMU.magbias[2] = 0.0;

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
    IMU.mx = magScale_x*((float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - IMU.magbias[0]);
    IMU.my = magScale_y*((float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - IMU.magbias[1]);
    IMU.mz = magScale_z*((float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - IMU.magbias[2]);


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

  maxx = _max(IMU.mx, maxx); minx = _min(IMU.mx, minx);
  maxy = _max(IMU.my, maxy); miny = _min(IMU.my, miny);
  maxz = _max(IMU.mz, maxz); minz = _min(IMU.mz, minz);

  biasx = (maxx + minx)/2;
  biasy = (maxy + miny)/2;
  biasz = (maxz + minz)/2;

  scalex = (maxx - minx)/2;
  scaley = (maxy - miny)/2;
  scalez = (maxz - minz)/2;

  float scale = (scalex + scaley + scalez)/3.0;
  scalex = scale/scalex;
  scaley = scale/scaley;
  scalez = scale/scalez;

  // Serial print and/or display at 0.5 s rate independent of data rates
  IMU.delt_t = millis() - IMU.count;

  // update LCD once per half-second independent of read rate
  // if (IMU.delt_t > 500)
  if (IMU.delt_t > 100)
  { 
    // M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextFont(2);

    M5.Lcd.setCursor(0, 0); M5.Lcd.print("     x       y       z ");
    M5.Lcd.setCursor(0,  24);
    M5.Lcd.printf("% 6.3f  % 6.3f  % 6.3f      raw  \r\n",  IMU.mx, IMU.my, IMU.mz);
    M5.Lcd.setCursor(0,  44);
    M5.Lcd.printf("% 6.3f  % 6.3f  % 6.3f      max  \r\n",  maxx, maxy, maxz);
    M5.Lcd.setCursor(0,  64);
    M5.Lcd.printf("% 6.3f  % 6.3f  % 6.3f      min  \r\n",  minx, miny, minz);
    M5.Lcd.setCursor(0,  84);
    M5.Lcd.printf("% 6.3f  % 6.3f  % 6.3f      bias  \r\n",  biasx, biasy, biasz);
    M5.Lcd.setCursor(0,  104);
    M5.Lcd.printf("% 6.3f  % 6.3f  % 6.3f      scale  \r\n",  scalex, scaley, scalez);

    IMU.count = millis();
    IMU.sumCount = 0;

  } // if (IMU.delt_t > 500)
}

/*
 * Required Libraries:
 * Blynk (https://github.com/blynkkk/blynk-library)
 * BamBotMotorDriver (https://github.com/garmstrong456/BamBotMotorDriver)
 * Adafruit-MCP23008 (https://github.com/adafruit/Adafruit-MCP23008-library)
 * ESP32-BLE (https://github.com/nkolban/ESP32_BLE_Arduino)
 * M5Stack (https://goo.gl/gBB9vF)
 *
 * How to manually install these libraries: https://www.arduino.cc/en/guide/libraries#toc5
 * The M5Stack library download contains changes important for compatibility with Blynk!
 * 
 * Setup:
 * Enable Bluetooth in your mobile device's settings.
 *  
 * Download the Blynk App from the App Store or Google Play Store.
 * Create a new project with any name.
 * Under "Choose Device", select "ESP32 Dev Board".
 * Under "Connection Type", select "BLE".
 * Go to the project's settings, find your "Auth Token" and
 * type it into the global variable auth[].
   * If you are too lazy to type this out, check your inbox because 
   * Blynk may have emailed your Auth Token to you.
 * Find and change global variable deviceName[] to the name of your device.
 * 
 * Create 4 buttons
 * Name them and configure them with the appropriate settings:
   * "Forward": V0
   * "Backward": V1
   * "Left": V2
   * "Right": V3
 * 
 * Add a "BLE (beta)" widget, select it, and click "Connect BLE Device"
 * Once your device is online, find its name in the list.
   * Your device's name may not be first, scroll through the list of random data.
 * Once connected, click the play icon and start using your robot!
 * 
 * Notes:
 * Remeber to disable all serial commands if it interferes with motor control.
 * Even if your M5Stack says "ON", that does not guarentee it successfully connected to WiFi.
 *
 * Created by Harris Miller
 */

//#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BamBotMotorDriver.h>
#include "Adafruit_MCP23008.h"
#include <M5Stack.h>

// You must change these to match your settings!
char deviceName[] = "________";
char auth[] = "______________";

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

void bUpdate();

int bState = 0;
bool f, b, l, r;

// Button Forward
BLYNK_WRITE(V0){
  if(param.asInt()==1){
    bState = 1;
    f = true;
  } else {
    f = false;
  }
  bUpdate();
}

// Button Backward
BLYNK_WRITE(V1){
  if(param.asInt()==1){
    bState = 2;
    b = true;
  } else {
    b = false;
  }
  bUpdate();
}

// Button Left
BLYNK_WRITE(V2){
  if(param.asInt()==1){
    bState = 3;
    l = true;
  } else {
    l = false;
  }
  bUpdate();
}

// Button Right
BLYNK_WRITE(V3){
  if(param.asInt()==1){
    bState = 4;
    r = true;
  } else {
    r = false; 
  }
  bUpdate();
}

void bUpdate(){
  if(!(f || b || l || r)){
    motors.setSpeeds(0,0);
  } else {
    switch(bState){
      case 1:
        // Case Forward
        motors.setSpeeds(400,400);
        break;
      case 2:
        // Case Backward
        motors.setSpeeds(-400,-400);
        break;
      case 3:
        // Case Left
        motors.setSpeeds(-200,200);
        break;
      case 4:
        // Case Right
        motors.setSpeeds(200,-200);
        break;
    }
  }
}

void setup(){
  // Initializes M5Stack and motors
  M5.begin();
  Wire.begin();
  //Serial.begin(115200);
  //Serial.println("Waiting for connections...");
  
  // Begins Blynk services.
  Blynk.setDeviceName(deviceName);
  Blynk.begin(auth);
  
  mcp.begin();
  motors.init(mcp);
  motors.setSpeeds(0,0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("ON");
}

// DO NOT CHANGE THIS!
void loop(){
  Blynk.run();
}


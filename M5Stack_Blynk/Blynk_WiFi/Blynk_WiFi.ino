/*
 * PLEASE VIEW "README.md" BEFORE STARTING!!!
 * 
 * Required Libraries:
 * Blynk (https://github.com/blynkkk/blynk-library)
 * BamBotMotorDriver (https://github.com/garmstrong456/BamBotMotorDriver)
 * Adafruit-MCP23008 (https://github.com/adafruit/Adafruit-MCP23008-library)
 * 
 * Setup:
 * Create a shared WiFi connection from your laptop.
 *  Windows: this option is listed as "Mobile hotspot" in Settings.
 * Mac: https://www.google.com/search?q=hotspot+through+mac
   * You can name the network name and password to anything,
   * as long as you update the global variables ssid[] and pass[].
 *  
 * Download the Blynk App from the App Store or Google Play Store.
 * Create a new project with any name.
 * Under "Choose Device", select "ESP32 Dev Board".
 * Under "Connection Type", select "WiFi".
 * Go to the project's settings, find your "Auth Token" and
 * type it into the global variable auth[].
   * If you are too lazy to type this out, chec kyour inbox because 
   * Blynk may have emailed your Auth Token to you.
 * 
 * Create 4 styled button with the names:
 * "Forward", "Backward", "Left", and "Right"
 * For each button, select the appropriate output pin:
   * "Forward": V0
   * "Backward": V1
   * "Left": V2
   * "Right": V3
 * 
 * Click the Play icon and wait for your device to go online.
 * 
 * Notes:
 * Remeber to disable all serial commands if it interferes with motor control.
 * Even if your M5Stack says "ON", that does not guarentee it successfully connected to WiFi.
 *
 * Created by Harris Miller
 */
 
//#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <BamBotMotorDriver.h>
#include "Adafruit_MCP23008.h"


// You must change these to match your settings!
char auth[] = "__________";
char ssid[] = "__________";
char pass[] = "__________";

int bState = 0;
bool f, b, l, r;

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

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
    // Stops all motors
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
  mcp.begin();
  motors.init(mcp);
  motors.setSpeeds(0,0);

  // Begins Blynk services.
  Blynk.begin(auth, ssid, pass);
  
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("ON");
}

// DO NOT CHANGE THIS!
void loop(){
  Blynk.run();   
}


/* Automatic Obstacle Avoid
 *  
 *  Author: Zifan He
 * 
 * This code is specifically for robot to avoid obstacle. Some other functions includes changing speed initially and flashing light to aware users that
 * the robot is avoiding the obstacle.
 * PIN CONNECTION:
 * 
 * Ultrasonic Sensor:
 * Trig ---> G2/2
 * Echo ---> G5/5
 * 
 * NeoPixel LED:
 * Input ---> 18 (don't ask me why I set 19 in the code!! It just work !!!)
*/

#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"
#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;


int forwardspeed = 100;
int turningspeed = 100;
int distance;

NewPing sonar(2,5,500);
Adafruit_NeoPixel light = Adafruit_NeoPixel(1, 19, NEO_RGB);

void setup() {
  //initialize M5
  M5.begin();
  //initialize mcp
  mcp.begin();
  //set motor and flip the direction of one
  motors.init(mcp);

  motors.flipM1(true);
  //initialize the LED
  light.setBrightness(100);
  light.begin();
  light.setPixelColor(0, 0, 0, 255);
  light.show();
}


void loop() {
  //press button c to start driving
  while(M5.BtnC.isPressed() == false){
  //change driving speed by button A
  if(M5.BtnA.wasPressed()){
    if(forwardspeed < 400){
      forwardspeed = forwardspeed + 10;
    }
    else{
      forwardspeed = forwardspeed - 300;
    }
    confirmed();
  }
  //change turning speed by button B
  if(M5.BtnB.wasPressed()){
    if(turningspeed < 400){
      turningspeed = turningspeed + 10;
    }
    else{
      turningspeed = turningspeed - 300;
    }
    confirmed();
  }
  M5.update();
  M5.Lcd.setCursor(0,0,2);
  M5.Lcd.print("FORWARD SPEED: ");
  M5.Lcd.print(forwardspeed);
  M5.Lcd.print(". \n\r");
  M5.Lcd.print("TURNING SPEED: ");
  M5.Lcd.print(turningspeed);
  M5.Lcd.print(".");
  }

  drivelight();
  distance = sonar.convert_cm(sonar.ping_median(5));
  if(distance < 20){
    M5.Lcd.setCursor(0,5,2); M5.Lcd.clear(); 
    M5.Lcd.print("DISTANCE: ");
    M5.Lcd.print(distance);
    motors.setSpeeds(0-turningspeed,turningspeed);
    avoidlight();
    delay(300);
  }
  else{
    motors.setSpeeds(forwardspeed, forwardspeed);
    M5.Lcd.setCursor(0,0,2); M5.Lcd.clear();
    M5.Lcd.print("Forward enabled:");
    M5.Lcd.print(distance); 
    drivelight();
    delay(50);
  }

}
// color of light when setting the velocity
void confirmed(){
    light.setPixelColor(0, 0, 255, 0); // Green
    light.show();
    delay(1000);
    light.setPixelColor(0, 0, 0, 255);
    light.show();
  }
//color of light when avoiding
void avoidlight(){
    light.setPixelColor(0, 255, 0, 0); // Red
    light.show();
}
//color of light when driving
void drivelight(){
    light.setPixelColor(0, 0, 0, 255); //Blue
    light.show();
}

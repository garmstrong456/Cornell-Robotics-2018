/* MazeRunner
 *  
 *  Author: Brighton Lee
 * 
 * This code drives your robot forward until the ultrasonic sensor sees something, then it turns roughly 90 degrees to the left. If there is still something there (or if it gets stuck on a wall),
 * it should begin to back up about 2 feet with optional annoying beeping. This program can be used as a reference for the ultrasonic sensor. 
 * **IMPORTANT**: the wires connected to the sensor must correspond to the pins that are specified below. You can plug them into other pins, but you must change the program accordingly.
*/
#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"
#include <NewPing.h>                   //Using NewPing library which must be downloaded to run

#define TRIGGER_PIN  26  //sets the pin connected to the "trig" output pin on the sensor
#define ECHO_PIN     19  //sets the pin connected to the "echo" output pin on the sensor
#define MAX_DISTANCE 15  //sets how far the sensor can see
#define BEEP 1040        //sets the pitch of the optional annoying beeping

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

void setup() {
  M5.begin(115200);
  mcp.begin();
  
  motors.init(mcp);
}
void Proximity() {                          //main body of the program; called in void loop
  while(true)
  {
    M5.update();
    delay(50);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.print("Ping: ");
    M5.Lcd.print(sonar.ping_cm());          //writes the distance in centimeters that an object is in front... **IMPORTANT**: no object in line of sight = 0
    M5.Lcd.println("cm");
    M5.update();
    if (sonar.ping() == 0)                  //looks at microseconds until ping returns (also 0 if no object in front), and goes forward if there is nothing
    {
      delay(200);
      motors.setSpeeds(100, 100);
      M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Forward");
      delay(1000);
    }
    else                                    //turns if there is an obstacle
    {
      M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Turning...");
      motors.setSpeeds(175, -175);
      delay(750);
      M5.update();
      if (sonar.ping() > 0)                 //if obstacle is still there or new obstacle appears in an allotted time frame, backs up
      {
        motors.setSpeeds(-50, -50);
        //M5.Speaker.tone(BEEP);                     //Optional annoying back-up beeping
        delay(500);
        //M5.Speaker.mute();
        delay(500);
        //M5.Speaker.tone(BEEP);
        delay(500);
        //M5.Speaker.mute();
        delay(500);
        //M5.Speaker.tone(BEEP);
        delay(500);
        M5.Speaker.mute();
      }
    }
  }
}

void loop() {
  motors.setSpeeds(100, 100);
  M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Forward");
  Proximity();                                            //calls main body of program
}

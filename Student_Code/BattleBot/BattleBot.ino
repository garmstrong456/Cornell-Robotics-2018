/* BattleBot
 *  
 *  Author: Brighton Lee
 * 
 * 
 * This code drives your robot in a circle until the ultrasonic sensor sees an obstacle, and then your robot will violently charge the obstacle. This program can be used as a reference for the ultrasonic sensor. 
 * **IMPORTANT**: the wires connected to the sensor must correspond to the pins that are specified below. You can plug them into other pins, but you must change the program accordingly.
*/

#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"
#include <NewPing.h>                     //NewPing library that is essential to run this program (must be downloaded off of "Manage Libraries" screen)

#define TRIGGER_PIN  26  //sets the pin connected to the "trig" output pin on the sensor
#define ECHO_PIN     19  //sets the pin connected to the "echo" output pin on the sensor
#define MAX_DISTANCE 40  //sets how far the sensor can see

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

void setup() {
  M5.begin(115200);
  mcp.begin();
  
  motors.init(mcp);
}
void Proximity() {                 //main body of program; called in void loop
  while(true)
  {
    M5.update();
    delay(50);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.print("Ping: ");
    M5.Lcd.print(sonar.ping_cm());     //writes distance to object in cm; **IMPORTANT**: if there is nothing in front, it will read a 0.
    M5.Lcd.println("cm");
    M5.update();
    if (sonar.ping() > 0)              //looks at microseconds until sound returns; if it returns, then there is an obstacle, the value is greater than 0, and the robot drives forward
    {
      delay(200);
      motors.setSpeeds(400, 400);
      M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Forward");
      delay(1000);
    }
    else                                //if there is no obstacle, the robot continues to search (spin around)
    {
      motors.setSpeeds(175, -175);
      M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Searching...");
    }
  }
}

void loop() {
  motors.setSpeeds(400, 400);
  M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Forward");
  Proximity();                         //Calls main body of program
}

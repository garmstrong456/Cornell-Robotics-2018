#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

/*
 * drive_with_encoders
 * 
 * Greg Armstrong July 2018
 * 
 * Drive back and forth while displaying the current position of the encoders
 * 
 * ----------------------
 * Wiring for this sketch
 * ----------------------
 * 
 * Motor Wires
 * EN_A --> M5Stack GPIO 3/R0 (speed pin)
 * EN_B --> M5Stack GPIO 1/T0 (speed pin)
 * PH_A --> MCP 7 (direction pin)
 * PH_B --> MCP 6 (direction pin)
 * 
 * Encoder Wires
 * Motor 1 wire 1 --> 16/R2
 * Motor 1 wire 2 --> 17/T2
 * Motor 2 wire 1 --> 2/G2
 * Motor 2 wire 2 --> 5/G5
 * 
 */

int s = 200;

void setup() {
  //Always call this first to avoid problems
  M5.begin();

  //initialize the MCP
  mcp.begin();
  
  motors.init(mcp);

  //Uncomment these to reverse one or both motors
  //motors.flipM1(true);
  //motors.flipM2(true);

  motors.attachEncoders(2, 5, 16, 17);

  M5.Lcd.setCursor(0,20,2); M5.Lcd.print("M1 pos: ");
  M5.Lcd.setCursor(0,35,2); M5.Lcd.print("M2 pos: ");
}

//Drive back and forth while displaying the position
void loop() {
  //set the speed
  motors.setSpeeds(s, s);
  
  //Wait for 1 second while updating the positions of the encoders
  uint32_t t = millis();
  while (millis() < (t + 1000)) {
    M5.Lcd.setCursor(80,20,2); M5.Lcd.print(motors.motor1Position()); M5.Lcd.print("      ");
    M5.Lcd.setCursor(80,35,2); M5.Lcd.print(motors.motor2Position()); M5.Lcd.print("      ");
  }

  //reverse directions
  s = -s;
}

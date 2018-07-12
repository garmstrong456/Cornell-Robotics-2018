#include <BamBotMotorDriver.h>
#include <M5Stack.h>
#include "Adafruit_MCP23008.h"
#include <NewPing.h>

#define TRIGGER_PIN  2  //sets the pin connected to the "trig" output pin on the sensor
#define ECHO_PIN     5 //sets the pin connected to the "echo" output pin on the sensor
#define MAX_DISTANCE 60  //sets how far the sensor can see\

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BamBotMotorDriver motors;
Adafruit_MCP23008 mcp;

int pingCM = 0;
int pingAvrg = 0;
int servoPin = 19;
int Angle = 0;
int oldAngle = 0;

int servoPulse(int angleDegrees)
{
  int pulseWidth = map(angleDegrees, 0, 180, 544, 2500);
  return pulseWidth;
}

void servoSet(int oldAngle, int newAngle) {
  int pulseWidth;
  if (oldAngle == newAngle)
  { 
    return;
  }
  else if (oldAngle < newAngle)
  {
    for (int i = oldAngle; i <= newAngle; i++){
      pulseWidth = servoPulse(i);
      digitalWrite(servoPin, HIGH);
       delayMicroseconds(pulseWidth); 
      digitalWrite(servoPin, LOW);
      delayMicroseconds(20000 - pulseWidth); 
    }
  }
  else if (oldAngle > newAngle)
  {
    for (int i = oldAngle; i >= newAngle; i--){
      pulseWidth = servoPulse(i);
      digitalWrite(servoPin, HIGH);
      delayMicroseconds(pulseWidth); 
      digitalWrite(servoPin, LOW);
      delayMicroseconds(20000 - pulseWidth);
    }
  }
}

void setAngle() {
  if (Angle > 150)
  {
    oldAngle = Angle;
    Angle = 0;
  }
  else 
  {
    oldAngle = Angle;
    Angle += 90;
  }
}

void setup() {
  m5.begin();
  mcp.begin();
  motors.init(mcp, 16, 7, 17, 6);
  pinMode(servoPin, OUTPUT);
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextColor(0x7bef);
  M5.Lcd.setCursor(60, 215);
  M5.Lcd.printf("Angle +");
}





void updateScreen()
{
  pingCM = sonar.ping_cm();
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.print("Ping: ");
  M5.Lcd.print(pingCM);
  M5.Lcd.print(" cm");
}

void PingAverage() {
    pingCM = sonar.ping_cm();
    updateScreen();
    M5.Lcd.setCursor(0, 20, 2);
    M5.Lcd.print("Scanning");
    pingAvrg += pingCM;
    delay(50);
    pingCM = sonar.ping_cm();
    updateScreen();
    M5.Lcd.setCursor(0, 20, 2);
    M5.Lcd.print("Scanning.");
    pingAvrg += pingCM;
    delay(50);
    pingCM = sonar.ping_cm();
    updateScreen();
    M5.Lcd.setCursor(0, 20, 2);
    M5.Lcd.print("Scanning..");
    pingAvrg += pingCM;
    delay(50);
    pingCM = sonar.ping_cm();
    updateScreen();
    M5.Lcd.setCursor(0, 20, 2);
    M5.Lcd.print("Scanning...");
    pingAvrg += pingCM;
    delay(50);
    pingCM = sonar.ping_cm();
    updateScreen();
    M5.Lcd.setCursor(0, 20, 2);
    M5.Lcd.print("             ");
    pingAvrg += pingCM;
    pingAvrg /= 5;
}





void loop() {
  M5.update();
    setAngle();
    servoSet(oldAngle, Angle);
    delay(2000);
  }

#include <ESP32_Servo.h>
#include <M5Stack.h>
#include <SharpDist.h>
Servo myServo;

int distance;

void setup() {
  M5.begin();
  myServo.attach(26, 500, 2500);
  
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0,0,2);
  M5.Lcd.print("Distance: "); M5.Lcd.print("ODD");

  if (M5.BtnA.wasPressed()){
    myServo.write(180);
  }
  if (M5.BtnB.wasPressed()){
    myServo.write(90);
  }
  if (M5.BtnC.wasPressed()){
    myServo.write(0);
  }
}

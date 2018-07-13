#include <M5Stack.h>
#include <BamBotMotorDriver.h>
#include <Adafruit_MCP23008.h>

BamBotMotorDriver motors;

void setup() {
  M5.begin();
  motors.initRed();
}

void loop() {
  M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Reverse");
  motors.setSpeedsRed(-150, -150);
  delay(1000);
  M5.Lcd.setCursor(0,0,2); M5.Lcd.print("Forward");
  motors.setSpeedsRed(150, 150);
  delay(1000);

}

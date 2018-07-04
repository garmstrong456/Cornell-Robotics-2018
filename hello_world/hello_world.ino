#include <M5Stack.h>

void setup() {
  M5.begin();
}

void loop() {
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.print("Hello World");

  delay(1000);

  M5.Lcd.clear();

  delay(1000);
}

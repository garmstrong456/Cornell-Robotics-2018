#include <M5Stack.h>

#define SERVO_0 2000 //Sets the lower limit for servo position
#define SERVO_180 8188 //Sets the upper limit for servo position
#define SERVO_CHANNEL 2 //the channel number is used for ledc writes instead of the pin number
#define SERVO_PIN 2 //the pin number is only used to configure the servo channel in setup
#define SERVO_PWM_FREQ 50 //common frequency that works with most servos
#define SERVO_TIMER_RES 16

int servoPosition = 0;
int servoPulse = SERVO_0;
//unsigned long currentMillis = 0; //will store current millisecond count
//unsigned long previousMillis = 0; // will store last time servo position was updated in sweep
//int sweepInterval = 1000; //interval in milliseconds used for sweeping movements
//int sweepIncrement = 1; //interval in "degrees" that servo moves in each sweep interval

//function to convert servo position in degrees to the corresponding pulse width
int degreesToPulse(int servoPosition){
  int servoPulse = map(servoPosition, 0, 180, SERVO_0, SERVO_180);
  return servoPulse;
}


//function to move servo at best speed to new position
void setServo(int servoPosition){
  //use ledc to set servo position using degreesToPulse function
  servoPulse=degreesToPulse(servoPosition);
  ledcWrite(SERVO_CHANNEL, servoPulse);
  M5.Lcd.fillScreen(0x0000);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(14, 14);
  M5.Lcd.printf("Servo Position = ");
  M5.Lcd.print(servoPosition);
  M5.Lcd.setCursor(14, 42);
  M5.Lcd.printf("Servo Pulse = ");
  M5.Lcd.print(servoPulse);
  M5.update();
      
  //need something to store last servo position so we can sweep from there to new position
  //int lastPosition = servoPosition;
}

//function to sweep servo at slower controlled rate from current position to new position
/*
void sweepServo(int servoPosition){
  //use ledc to sweep to a position using setServo and the servo

  //sweep interval and increment with millis
  currentMillis = millis();
  if(currentMillis - previousMillis > sweepInterval){


  }  
}
*/  
void setup() {
  // Debug console
  M5.begin();
  ledcSetup(SERVO_CHANNEL, SERVO_PWM_FREQ, SERVO_TIMER_RES);
  ledcAttachPin(SERVO_PIN, SERVO_CHANNEL);
}

 
void loop() {
  setServo(60);
  delay(350);
  setServo(110);
  delay(700);
}




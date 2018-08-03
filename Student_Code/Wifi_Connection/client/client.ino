/*
    This sketch sends a message to a TCP server

*/

#include <WiFi.h>
#include <WiFiMulti.h>
#include <M5Stack.h>

WiFiMulti WiFiMulti;

void setup()
{
  M5.begin();
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFiMulti.addAP("fsp");
  /* if your wifi has an password, use 
   *  WiFiMulti.addAP("SSID","your password here")
   */

  M5.Lcd.println();
  M5.Lcd.println();
  M5.Lcd.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    M5.Lcd.print(".");
    delay(500);
  }

  M5.Lcd.println("");
  M5.Lcd.println("WiFi connected");
  M5.Lcd.println("IP address: ");
  M5.Lcd.println(WiFi.localIP());

  delay(500);
}


void loop()
{
  //M5.update();

  //if (M5.BtnA.wasPressed()) {
  const uint16_t port = 80;
  const char * host = "192.168.43.16"; // ip or dns
  M5.Lcd.print("connecting to ");
  M5.Lcd.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    M5.Lcd.println("connection failed");
    M5.Lcd.println("wait 5 sec...");
    delay(5000);
    return;
  }
  //}

  //if (M5.BtnB.isPressed()) {
  // This will send the request to the server
  M5.Lcd.print("Send this data to server");
  M5.Lcd.println(" =nah= ");
  //WiFiClient client;//
  client.write(" =nah= ");
  //}

  //read back one line from server
  String line = client.readStringUntil('\r');
  M5.Lcd.println(line);
   String lin = client.readStringUntil('\r');
  M5.Lcd.println(lin);
  //M5.Lcd.println(client.read());

  //if (M5.BtnC.wasPressed()) {
  M5.Lcd.println("closing connection");
  //WiFiClient client;//
  M5.Lcd.print(client.read());

  client.stop();
  M5.Lcd.println("wait 5 sec...");
  delay(5000);//delay time need to be shortened to make game feasib
  
}
//}

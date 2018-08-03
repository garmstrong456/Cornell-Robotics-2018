#include <WiFi.h>

const char* ssid     = "fsp"; // The connection of this two m5 requies a WAN to support, it could be a Hotspot or WiFi, put the name of the wifi that you want the two m5 to connect 
const char* password ="";// put the password of this WiFi

WiFiServer server(80);

void setup()
{
  //to make it simpler to debug, we didn't use "m5.begin()", you may upgrade this part
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid);   //login

  while (WiFi.status() != WL_CONNECTED) {   //detect whether connected or not
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  Serial.print("what do you want to send");
  Serial.println();
  delay(1000);
char he = Serial.read();
delay(500);
  WiFiClient client = server.available();   // listen for incoming clients
     client.write(he);
    client.write("Do you want to build an snowman?");   //send your data
   //The code below is used to sent a message to the client connected to this server
  // The code segmant below is used to recieve a message from a client connected to this server
  if (client) {                             // if you get a client,
    Serial.println("New Client.");          // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
        }
      }
    }
  }
  // close the connection:
 // client.stop();
 // Serial.println("Client Disconnected.");
  delay(20);
}

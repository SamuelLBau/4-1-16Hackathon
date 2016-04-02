/*
 Chat  Server

 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.


 Circuit:
 * WiFi shield attached

 created 18 Dec 2009
 by David A. Mellis
 modified 31 May 2012
 by Tom Igoe

 */
#include "wifiChat.h"
wifiChat WIFI;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Made it before WIFI.begin");
  WIFI.begin();
  Serial.println("Made it after WIFI.begin");
}


void loop() 
{
  Serial.println("In main loop");
  if(WIFI.sendData("HelloAgain\n"));
    WIFI.tryConnect();
  delay(1000);
}

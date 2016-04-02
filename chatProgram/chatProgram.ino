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
#include "WifiMessageParser.h"
wifiChat WIFI;
int i = 0;
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
  Serial.print("I = ");Serial.println(i++);
  handleWifiRequests();


  //if(WIFI.sendData("HelloAgain\n"));
  //  WIFI.tryConnect();
  delay(100);
}
void handleWifiRequests()
{
  Serial.println("Checking for Wifi Request");
  String s = WIFI.checkForRequest();
  if(s == "")
    return;

  Serial.print("Request received: ");
  Serial.println(s);
  int index = s.indexOf(":");
  String prefix = s.substring(0,index);
  String followingString = s.substring(index+1);
  if(prefix == COMMAND_ID)
  {
    handleWiFiCommand(followingString);
  }
  else if(prefix == REQUEST_ID)
  {
    handleWiFiRequest(followingString);
  }
  else if(prefix == REQUESTALL_ID)
  {
    handleWiFiRequestAll();
  }
}
void handleWiFiCommand(String commandString)
{ 
  int index = commandString.indexOf(":");
  String command = commandString.substring(0,index);
  String value = commandString.substring(index+1);
  //The command string should have a semi-colon so the command can include Data
  if(command == HANDSHAKE)
  {
    //handshake just expects the value to be returned to it
    WIFI.sendData(value);
  }
}
void handleWiFiRequest(String request)
{
  //The request string should just have the id of the requested data
}
void handleWiFiRequestAll()
{
  //This should generate a response with every valid data field
}


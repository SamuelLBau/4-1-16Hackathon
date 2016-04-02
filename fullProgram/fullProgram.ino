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
#include "Touchpad.h"
#include "LCDisplay.h"
wifiChat WIFI;
Touchpad TP;
LCDisplay LCD;

int i = 0;
String adminPW = "hackathon";
String defaultPIN = "1111";
String state_locked = "True";
String state_open = "False";
String state_lockdown = "False";
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Made it before WIFI.begin");
  WIFI.begin();
  Serial.println("Made it after WIFI.begin");
  TP.begin();
  TP.setPW(defaultPIN);

  LCD.begin();
}


void loop() 
{
  Serial.println("In main loop");
  Serial.print("I = ");Serial.println(i++);
  Serial.print("state_locked");Serial.println(state_locked);
  Serial.print("state_open");Serial.println(state_open);
  Serial.print("state_lockdown");Serial.println(state_lockdown);
  Serial.print("adminPW");Serial.println(adminPW);
  Serial.print("PIN");Serial.println(TP.getPW());

  //These lines update the state of the lockbox
  handleWifiRequests();
  TP.updateData();
  //state_open = FS.isOpen();
  lockedLogic(); //This edits state_locked

  

  //These display data on devices
  displayOnLCD(); //Will probably just write safe is LOCKED / IN LOCKDOWN
  displayOnLED(); //Hopefully will be able to add some state LEDS
  delay(100);
}
String lockedLogic()
{
  if(state_lockdown == "True")
  {
    state_locked = "True";
  }
  else
  {
    if(TP.isPWAccepted())
    {
      state_locked = "False";
    }
  }
}
void displayOnLCD()
{
  if(state_locked == "True")
  {
    LCD.writerow1("Box is locked");
  }
  else
  {
    LCD.writerow1("Box is unocked");
  }
  if(state_lockdown == "True")
  {
    LCD.writerow2("Lockdown enabled");
  }
  else
  {
    LCD.writerow2("Lockdowndisabled");
  }
}
void displayOnLED()
{
  
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
  if(command == ATTEMPT_PIN_UNLOCK)
  {
    if(TP.compareToPW(value))
    {
      Serial.println("WIFI-PIN was accepted");
      TP.setPWAcceptedTrue();
      WIFI.sendData("True");
    }
    else
    {
      WIFI.sendData("False");
      Serial.println("WIFI-PIN was not accepted");
    }
  }
  if(command == CHECK_ADMIN_PW)
  {
    if(value ==adminPW)
    {
      WIFI.sendData("True");
    }
    else
    {
      WIFI.sendData("False");
    }
  }
  if(command == UPDATE_ADMIN_PW)
  {
    adminPW = value;
     WIFI.sendData(COMMAND_RECEIVED);
  }
  if(command == UPDATE_PIN)
  {
    TP.setPW(value);
    WIFI.sendData(COMMAND_RECEIVED);
  }
  if(command == UPDATE_LOCKDOWN)
  {
    state_lockdown = value;
    WIFI.sendData(COMMAND_RECEIVED);
  }
  if(command == LOCK_SAFE)
  {
    //TODO Add all other lock checks
    TP.setPWAcceptedFalse();
  }
  
}
void handleWiFiRequest(String request)
{
  //The request string should just have the id of the requested data
  if(request == STATE_OPEN)
  {
    WIFI.sendData(state_open);
  }
  if(request == STATE_LOCKED)
  {
    WIFI.sendData(state_locked);
  }
  if(request == STATE_LOCKDOWN)
  {
    WIFI.sendData(state_lockdown);
  }
}
void handleWiFiRequestAll()
{
  String s = STATE_OPEN;s.concat(":");s.concat(state_open);s.concat("\n");
  s.concat(STATE_LOCKED);s.concat(":");s.concat(state_locked);s.concat("\n");
  s.concat(STATE_LOCKDOWN);s.concat(":");s.concat(state_lockdown);s.concat("\n");
  WIFI.sendData(s);
  //This should generate a response with every valid data field
}


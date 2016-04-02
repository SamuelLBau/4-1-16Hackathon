#include <SPI.h>
#include <WiFi101.h>
#include "wifiChat.h"
#include "WiFiMessageParser.h"

wifiChat::wifiChat()
{
  //begin();
}
int wifiChat::begin()
{
  
  ssid = "Connectify-21"; //  your network SSID (name)
  pass = "importteam";    // your network password (use for WPA, or use as key for WEP)
  keyIndex = 0;            // your network key Index number (needed only for WEP)
  status = WL_IDLE_STATUS;
  alreadyConnected = false; // whether or not the client was connected previously
  WiFiServer tserver = WiFiServer(23);
  server=tserver;
  return 0;
  //return tryConnect();
}
String wifiChat::checkForRequest()
{
  tryConnect();
  String requestString = "";
  WiFiClient client = server.available();
  //Serial.println(client);
  if(!client) 
    return requestString;

  //Serial.print("Client.available() = ");
  //Serial.print(client.available());
  if (client.available() > 0) {
    
    char thisChar = client.read();
    while(thisChar != '\n' && client.available() > 0)
    {
      requestString.concat(thisChar);
      thisChar = client.read();
    }
  }
  return requestString;
    
}
int wifiChat::tryConnect()
{
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    return -2;
  }
  // attempt to connect to Wifi network:
  if(server.available() > 0)
    return 0;

  short numAttempts = 0;
  status = WiFi.status();
  if(status == WL_CONNECTED)
    return 0;
  while ( status != WL_CONNECTED && numAttempts <= NUM_CONNECT_ATTEMPTS) 
  {
    numAttempts++;
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    //CONNECTION METHOD
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(CONNECTION_DELAY);
  }

  // start the server:
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
  return 0;
}

void wifiChat::printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
int wifiChat::sendData(String outString)
{
  //WiFiClient client = server.available();
  if(!client.connected())
    client = server.available();
    
  if(!client.connected()) 
    return -1;

  client.flush();
  char outChar[25];
  outString.concat(END_TRANSMISSION);
  outString.toCharArray(outChar,25);
  client.write(outChar);client.write("\r\n");
  Serial.print("Writing across WiFi: ");
  Serial.println(outChar);

  //client.write("Quit");client.write("\r\n");
  //Serial.print("Writing across WiFi: ");
  //Serial.print("Quit");
  
  return 0;
  
}

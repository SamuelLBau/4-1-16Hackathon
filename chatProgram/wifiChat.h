#ifndef wifiChat_h
#define wifiChat_h

#include "Arduino.h"
#include <SPI.h>
#include <WiFi101.h>

//Assume Serial.begin() already called
#define NUM_CONNECT_ATTEMPTS 1  //How many times attempt to connect to wifi
#define CONNECTION_DELAY 10000 //How long to wait for each connection attempt (ms)





class wifiChat
{
  public:
    wifiChat();
    int begin();
    int tryConnect();
    String checkForRequest();
    int sendData(String);
  private:
    String ssid; //  your network SSID (name)
    String pass;    // your network password (use for WPA, or use as key for WEP)
    int keyIndex;            // your network key Index number (needed only for WEP)
    int status;
    WiFiServer server = WiFiServer(23);
    WiFiClient client;
    boolean alreadyConnected; // whether or not the client was connected previously
    void printWifiStatus();
    
};
#endif

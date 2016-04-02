import getpass
import sys
import telnetlib


enable = True

class telnetComs():
    
    #This is the list of commands
    endTransmission = "Quit"
    handShakeCommand = "handshake"
    handShakeValue = "Hackathon 2016"
    
    commandString = "command"
    requestDataString = "request"
    requestAllDataString = "reqAll"
    commandReceivedString = "CR"
    def __init__(self=None,ip="192.168.46.131"):
        self.ipID = ip
        self.connected = False
        self.attemptConnect()
    def attemptConnect(self):
        if(enable):
            #print("Attempting to connect to %s"%(self.ipID))
            self.tn = telnetlib.Telnet(self.ipID,timeout=5)
        self.writeLine(self.commandString +":" +self.handShakeCommand+ ":"+self.handShakeValue);
        response = self.readResponse()
        print("Response      : %s"%(response))
        print("HandShakeValue: %s"%(self.handShakeValue))
        self.connected = True
        if(response != self.handShakeValue):
            print("Handshake failed")
            self.connected = False;
            return
        else:
            print("Handshake succeeded")
    def requestData(self,key):
        if(not self.connected):
            self.attemptConnect()
            if(not self.connected):
                return ""
        self.writeLine(self.requestDataString + ":"+key)
        response = self.readResponse()
        print("Request for %s response %s"%(key,response))
        return response
        
    def requestAllData(self):
    #this should return a dictionary of valid items
        if(not self.connected):
            self.attemptConnect()
            if(not self.connected):
                return ""
        self.writeLine(self.requestAllDataString + ":")
        response = self.readResponse()
        print("AllDataResponse: \n%s"%(response))
        return response
        
    def sendCommand(self,command,value=""):
        print("About to send command %s:%s"%(command,value))
        if(not self.connected):
            self.attemptConnect()
            if(not self.connected):
                return ""
        self.writeLine(self.commandString +":" + command+":"+value)
        response = self.readResponse()
        return response
    def writeLine(self,string):
        if(enable):
            #print("Writing to Wifi: %s"%(string+"\n"))
            self.tn.write(string+"\n")
            return
        return
    def readResponse(self):
        if(enable):
            response = self.tn.read_until(self.endTransmission,timeout=1)
            response = response.replace(self.endTransmission,"").replace("\0","")
            return response
        else:
            return ""
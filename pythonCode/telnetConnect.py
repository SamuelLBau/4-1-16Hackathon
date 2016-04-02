import getpass
import sys
import telnetlib




class telnetComs():
    handShakeInit = "Hello SAMD21"
    requestDataString = "request"
    requestAllDataString = "requestAll"
    doneString = "QUIT"
    def __init__(self=None,ip="192.168.1.1"):
        ipID = ip
        
        tn = telnetlib.Telnet(HOST)
        tn.write(self.handShakeInit)
        if(tn.read_eager() != self.handShakeInit):
            print("Handshake failed, quitting")
            return -1
        
    def requestData(self,key):
        tn = tn.write(self.requestAllDataString + ":"+key)
        value = tn.read_eager()
        return value
        
    def requestAllData(self):
    #this should return a dictionary of valid items
        tn = tn.write(self.requestAllDataString + ":")
        
        string = tn.read_until(self.doneString)
        
        print(string)
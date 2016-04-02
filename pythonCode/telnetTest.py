import getpass
import sys
import telnetlib

HOST = "192.168.46.101"
#user = raw_input("Enter your remote account: ")
#password = getpass.getpass()

tn = telnetlib.Telnet(HOST)
#delay(1000)

tn.write("Hello telnet\n")
tn.write("Hello\n")

val = tn.read_until("Quit",timeout=.2)

while(val == ""):
    
    print("Trying to get response")
    tn.write("Hello telnet\n")
    tn.write("Hello\n")
    val = tn.read_until("Quit",timeout=.2)
print "Printing val: %s" %(val)


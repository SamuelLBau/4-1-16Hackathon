import getpass
import sys
import telnetlib

HOST = "192.168.46.101"
#user = raw_input("Enter your remote account: ")
#password = getpass.getpass()

tn = telnetlib.Telnet(HOST)

#tn.write("Hello telnet\n")
val = tn.read_all()
print "Printing val: %s" %(val)

val2 = tn.read_until("Quit")
print("Printing read until %s" %(val2))


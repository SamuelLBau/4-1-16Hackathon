import getpass
import sys
import telnetlib

HOST = "192.168.46.101"
#user = raw_input("Enter your remote account: ")
#password = getpass.getpass()

tn = telnetlib.Telnet(HOST)

tn.write("Hello telnet")

print tn.read_until("Quit")
import Tkinter as tk
from mainFrame import mainFrame
from telnetConnect import telnetComs
from getAdminPWDialog import getAdminPW
from adminOptionsDialog import adminOptionsDialog


class Application(tk.Toplevel):
    #THESE MUST MATCH VALUES IN WiFiMessageParser
    tryTouchpadCode =   "tryTPCode"
    checkAdminPWID =    "checkAdminPW"
    updateAdminPWID =   "updateAPW"
    updatePINID =       "updatePIN"
    updateLockdown =    "updateLockdown"
    def __init__(self,parent=None):
        tk.Toplevel.__init__(self,parent,bg='#F0F0F0',bd=1,relief='sunken')
        
        self.WiFiCOM = telnetComs(ip="192.168.46.101")
        
        self.setupMenus()
        
        self.placeWidgets()
        
        
    def placeWidgets(self):
        self.mainFrame = mainFrame(self,self.sendCompleteTouchCode,self.sendCompleteEncoderCode)
        
        
        self.mainFrame.grid()
        
    def setupMenus(self):
        self.menuBar = tk.Menu(self)
        
        self.adminMenu = tk.Menu(self.menuBar,tearoff=0)
        self.adminMenu.add_command(label="View Admin. Options",command=self.openAdminFrame)
        
        self.menuBar.add_cascade(label="Admin",menu=self.adminMenu)
        
        self.config(menu=self.menuBar)
        
        
    def openAdminFrame(self):
        dialog = getAdminPW(self.checkAdminPW)
        
    def checkAdminPW(self,PW):
        #Check controller for validity
        #If error, open error dialog
        #If correct, open admin options dialog
        print("Password input was %s"%(PW))
        response = self.WiFiCOM.sendCommand(self.checkAdminPWID,PW)
        #if(response == "True"):
        #    self.openAdminOptionsDialog()
        self.openAdminOptionsDialog()   
        print("TODO: check controller for adminPW")
    def openAdminOptionsDialog(self):
        dialog = adminOptionsDialog(UAPW=self.sendUpdateAdminPassword,UPIN=self.sendUpdatePIN,
            ULD=self.sendUpdateLockdown)
    def sendUpdateAdminPassword(self,PW):
        response = self.WiFiCOM.sendCommand(self.updateAdminPWID,PW)
        
        print("TODO: send code to microcontroller, ask for if code accepted") 
    def sendUpdatePIN(self,PIN):
        #This is the touchpad code
        response = self.WiFiCOM.sendCommand(self.updatePINID,PIN)
        print("TODO: send code to microcontroller, ask for if code accepted") 
    
    def sendUpdateLockdown(self,state):
        response = self.WiFiCOM.sendCommand(self.updateLockdown,state)
        print("TODO: send code to microcontroller, ask for if code accepted") 
        
    def sendCompleteTouchCode(self,code):
        #Code is a string
        response = self.WiFiCOM.sendCommand(self.tryTouchpadCode,code)
        
        print("TODO: send code to microcontroller, ask for if code accepted")
        
        return -1
    def sendCompleteEncoderCode(self,code):    
        #Code is a string
        
        print("TODO: send code to microcontroller, ask for if code accepted")
        return -1
    def resetBothCodes(self):
        print("TODO: undo any accepted codes")
        
        
        
        #placeholder, return code provided by microcontroller
        return 1
        
    
        
        
root = tk.Tk()
root.withdraw()
top = Application(root)
top.protocol("WM_DELETE_WINDOW", root.destroy)
top.title('Remote Safe')
root.mainloop()

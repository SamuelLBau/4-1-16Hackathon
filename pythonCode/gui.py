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
    updateLock =        "updateLock"
    state_open =        "state_open"
    state_locked =      "state_locked"
    state_lockdown=     "state_lockdown"
    def __init__(self,parent=None):
        tk.Toplevel.__init__(self,parent,bg='#F0F0F0',bd=1,relief='sunken')
        
        self.WiFiCOM = telnetComs(ip="192.168.46.101")
        
        self.setupMenus()
        
        self.placeWidgets()
        
        
    def placeWidgets(self):
        self.mainFrame = mainFrame(self,self.sendCompleteTouchCode,self.sendCompleteEncoderCode,self.sendUpdateLock)
        
        
        self.mainFrame.grid()
        
    def setupMenus(self):
        self.menuBar = tk.Menu(self)
        
        self.adminMenu = tk.Menu(self.menuBar,tearoff=0)
        self.adminMenu.add_command(label="View Admin. Options",command=self.openAdminFrame)
        
        self.menuBar.add_cascade(label="Admin",menu=self.adminMenu)
        
        self.config(menu=self.menuBar)
        
        
    def openAdminFrame(self):
        dialog = getAdminPW(self.checkAdminPW)

    def openAdminOptionsDialog(self):
        dialog = adminOptionsDialog(UAPW=self.sendUpdateAdminPassword,UPIN=self.sendUpdatePIN,
            ULD=self.sendUpdateLockdown)
        
        print("TODO: send code to microcontroller, ask for if code accepted") 

#-------------BEGIN COMMANDS-------------------
    def sendCompleteTouchCode(self,code):
        #Code is a string
        response = self.WiFiCOM.sendCommand(self.tryTouchpadCode,code)
        print("tryTouchpadCode response %s"%(response))
        return response
        
    def sendCompleteEncoderCode(self,code):
        print("Do something with encoders")
    
    def checkAdminPW(self,PW):
        #Check controller for validity
        response = self.WiFiCOM.sendCommand(self.checkAdminPWID,PW)
        print("checkAdminPW response %s"%(response))
        if("True" in response):
            self.openAdminOptionsDialog()
        #self.openAdminOptionsDialog()   
    def sendUpdateAdminPassword(self,PW):
        response = self.WiFiCOM.sendCommand(self.updateAdminPWID,PW)
        print("sendUpdateAdminPassword response %s"%(response))
        return response
        
    def sendUpdatePIN(self,PIN):
        #This is the touchpad code
        response = self.WiFiCOM.sendCommand(self.updatePINID,PIN)
        print("sendUpdatePIN response %s"%(response))
        return response 
        
    def sendUpdateLockdown(self,state):
        response = self.WiFiCOM.sendCommand(self.updateLockdown,state)
        print("sendUpdateLockdown response %s"%(response))
        return response

    def sendUpdateLock(self,state):
        response = self.WiFiCOM.sendCommand(self.updateLock,state)
        print("sendUpdateLock response %s"%(response))
        return response

        
    
#-------------END COMMANDS-------------------       
#-----------BEGIN REQUESTS-------------------
    def requestStateOpen():
        response = self.WiFiCOM.requestData(self.state_open)
        #placeholder, return code provided by microcontroller
        return response
        
    def requestStateLocked():
        response = self.WiFiCOM.requestData(self.state_locked)
        #placeholder, return code provided by microcontroller
        return response
        
    def requestStateOLockdown():
        response = self.WiFiCOM.requestData(self.state_lockdown)
        #placeholder, return code provided by microcontroller
        return response
        
    def requestAll():
        response = self.WiFiCOM.requestAll()
        #placeholder, return code provided by microcontroller
        return response
        
#--------------END REQUESTS--------------------
        
    
        
        
root = tk.Tk()
root.withdraw()
top = Application(root)
top.protocol("WM_DELETE_WINDOW", root.destroy)
top.title('Remote Safe')
root.mainloop()

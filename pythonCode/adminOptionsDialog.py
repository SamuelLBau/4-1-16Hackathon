import Tkinter as tk

class adminOptionsDialog(tk.Toplevel):
    
    def __init__(self,UAPW,UPIN,ULD):
        self.updateAdminPW = UAPW
        self.updatePIN = UPIN
        self.updateLockdown = ULD
        
        tk.Toplevel.__init__(self,bg='#F0F0F0')
        self.title("Admin. options")
        
        self.placeWidgets()
        
    def placeWidgets(self):
        
        self.adminPWTV = tk.StringVar()
        self.adminPWTV.trace("w", lambda name, index, mode, adminPWTV=self.adminPWTV.get(): self.checkAdminPW())
        self.PINTV = tk.StringVar()
        self.PINTV.trace("w", lambda name, index, mode, PINTV=self.PINTV.get(): self.checkPIN())
        self.lockdownTV = tk.StringVar()
        self.lockdownTV.trace("w", lambda name, index, mode, lockdownTV=self.lockdownTV.get(): self.checkLockdown())
        
        self.adminPWTB = tk.Entry(self,width = 20,textvariable=self.adminPWTV)
        self.PINTB = tk.Entry(self,width = 20,textvariable=self.PINTV)
        self.lockdownTB= tk.Entry(self,width = 20,textvariable=self.lockdownTV,state="disabled")
        self.lockdownTB.config(disabledforeground= "black", disabledbackground="green")
        
        self.adminPWButton = tk.Button(self,text="Update Admin PW",command=self.beginUpdateAdminPW)
        self.PINButton = tk.Button(self,text="Update PIN",command=self.beginUpdatePIN)
        self.lockdownButton = tk.Button(self,text="Go into Lockdown",command=self.beginUpdateLockdown)
        self.lockdownState = "False"
        
        
        self.adminPWTB.grid(row=0,column=0)
        self.PINTB.grid(row=1,column=0)
        self.lockdownTB.grid(row=2,column=0)
        
        self.adminPWButton.grid(row=0,column=1,sticky="we")
        self.PINButton.grid(row=1,column=1,sticky="we")
        self.lockdownButton.grid(row=2,column=1,sticky="we")
        
        
        
    def beginUpdateAdminPW(self,event=None):
        val = self.adminPWTV.get()
        if(not ":" in val):
            self.updateAdminPW(val)
    
    def beginUpdatePIN(self,event=None):
        val=self.PINTV.get()
        try:
            int(val)
            self.updatePIN(val)
        except ValueError:
            self.PINTB.config(bg="red")
            
    def beginUpdateLockdown(self,event=None):
        self.changeLockDown()
        self.updateLockdown(self.lockdownState)
        
        
    def checkAdminPW(self):
        val = self.adminPWTV.get()
        if(":" in val):
            self.adminPWTB.config(bg="red")
        else:
            self.adminPWTB.config(bg="white")
        
    def checkPIN(self):
        val=self.PINTV.get()
        try:
            int(val)
            self.PINTB.config(bg="white")
        except ValueError:
            self.PINTB.config(bg="red")
    def checkLockdown(self):
        val=self.lockdownTV.get()
        #Nothing todo with this
        
    def changeLockDown(self,state=""):
        if(state != ""):
            if(state == "False"):
                self.lockdownState = "True"
            else:
                self.lockdownState = "False"
            
        
        if(self.lockdownState == "False"):
            self.lockdownTV = "Lockdown Enabled"
            self.lockdownButton.config(text="Lift Lockdown")
            self.lockdownTB.config(disabledbackground="red")
            self.lockdownState = "True"
        else:
            self.lockdownTV = "Lockdown Disabled"
            self.lockdownButton.config(text="Go into Lockdown")
            self.lockdownTB.config(disabledbackground="green")
            self.lockdownState = "False"
        
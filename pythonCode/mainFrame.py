import Tkinter as tk

from touchpadFrame import touchpadFrame as TPF


class mainFrame(tk.Frame):
    
    def __init__(self,master,SCTC,SCEC,SLB):
        tk.Frame.__init__(self,master,bg='#F0F0F0')
        self.setCompleteTouchCode = SCTC
        self.setCompleteEncoderCode = SCEC
        self.setLockBox = SLB;
        
        
        self.placeFrames()
        
        self.lockedStatus.set("Unlocked")
        self.openStatus.set("Open")
        
        #self.lockedStatus.set("Locked")
        self.openStatus.set("Closed")
        
        
    def placeFrames(self):
        self.lockedStatus = tk.StringVar()
        self.lockedStatus.trace("w", lambda name, index, mode, lockedStatus=self.lockedStatus.get(): self.lockedStatusChange())
        
        self.openStatus = tk.StringVar()
        self.openStatus.trace("w", lambda name, index, mode, openStatus=self.openStatus.get(): self.openStatusChange())
        
        self.lockedStatusTB = tk.Entry(self,width = 12,textvariable=self.lockedStatus,state="disable")
        self.openStatusTB = tk.Entry(self,width = 12,textvariable=self.openStatus,state="disable")
        self.openStatusTB.config(disabledforeground="black")
        self.lockedStatusTB.config(disabledforeground="black")
        
        self.lockedStatusTB.bind("<Button-1>",self.tryLockBox)
        
        self.touchpadFrame = TPF(self,self.setCompleteTouchCode)
        
        
        
        self.lockedStatusTB.grid(row=0,column=0)
        self.openStatusTB.grid(row=0,column=1)
        
        self.touchpadFrame.grid(row=1,column=0,columnspan = 2)
        
        
        
    def tryLockBox(self,event):
        self.setLockBox("True")

    def openStatusChange(self):
        if(self.openStatus.get() == "Open"):
            self.openStatusTB.config(disabledbackground="green")
        else:
            self.openStatusTB.config(disabledbackground="red")
            
    def lockedStatusChange(self):
        if(self.lockedStatus.get() == "Unlocked"):
            
            self.lockedStatusTB.config(disabledbackground="green")
        else:
            self.lockedStatusTB.config(disabledbackground="red")
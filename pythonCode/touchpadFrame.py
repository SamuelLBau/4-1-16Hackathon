import Tkinter as tk


class touchpadFrame(tk.Frame):
    #SCF is the function called to send the code to microcontroller
    def __init__(self,master,SCF):
        self.SCF=SCF
        self.WiFiCOM = telnet
        tk.Frame.__init__(self,master,bg='#F0F0F0')
        
        
        self.placeWidgets()
        
    def placeWidgets(self):
        self.currentCode = tk.StringVar()
        self.currentCode.trace("w", lambda name, index, mode, currentCode=self.currentCode.get(): self.empty())

        self.currentCodeTB = tk.Entry(self,width = 23,textvariable=self.currentCode)
        
        self.currentCodeTB.grid(row=0,column=0,columnspan=5)       
        
        self.placeButtons()
        
        
        
    def updateCurrentCode(self,num):
        string = self.currentCode.get()
        string = string + num
        self.currentCode.set(string)
        print("Appending to code %s"%(num))
        print("TODO: maybe make sure code is valid")
    def clearCurrentCode(self):
        self.currentCode.set("")
    def getCurrentCode(self):
        self.getCurrentCode.get()
    def empty(self):
        num=1
        
    def placeButtons(self):
        #This begins on row 1, returns row to place stuff on
        self.zeroButton = tk.Button(self,command=self.updateZeroButton,text="0")
        self.oneButton = tk.Button(self,command=self.updateOneButton,text="1")
        self.twoButton = tk.Button(self,command=self.updateTwoButton,text="2")
        self.threeButton = tk.Button(self,command=self.updateThreeButton,text="3")
        self.fourButton = tk.Button(self,command=self.updateFourButton,text="4")
        self.fiveButton = tk.Button(self,command=self.updateFiveButton,text="5")
        self.sixButton = tk.Button(self,command=self.updateSixButton,text="6")
        self.sevenButton = tk.Button(self,command=self.updateSevenButton,text="7")
        self.eightButton = tk.Button(self,command=self.updateEightButton,text="8")
        self.nineButton = tk.Button(self,command=self.updateNineButton,text="9")
        self.clearButton = tk.Button(self,command=self.updateClearButton,text="clear")
        self.enterButton = tk.Button(self,command=self.updateEnterButton,text="enter")
        
        
        self.oneButton.grid(row=1,column=0)
        self.twoButton.grid(row=1,column=1)
        self.threeButton.grid(row=1,column=2)
        self.fourButton.grid(row=2,column=0)
        self.fiveButton.grid(row=2,column=1)
        self.sixButton.grid(row=2,column=2)
        self.sevenButton.grid(row=3,column=0)
        self.eightButton.grid(row=3,column=1)
        self.nineButton.grid(row=3,column=2)
        self.clearButton.grid(row=4,column=0)
        self.zeroButton.grid(row=4,column=1)
        self.enterButton.grid(row=4,column=2)
        
        
    def updateZeroButton(self):
        self.updateCurrentCode(str(0))
    def updateOneButton(self):
        self.updateCurrentCode(str(1))
        
    def updateTwoButton(self):
        self.updateCurrentCode(str(2))
    def updateThreeButton(self):
        self.updateCurrentCode(str(3))
    def updateFourButton(self):
        self.updateCurrentCode(str(4))
    def updateFiveButton(self):
        self.updateCurrentCode(str(5))
    def updateSixButton(self):
        self.updateCurrentCode(str(6))
    def updateSevenButton(self):
        self.updateCurrentCode(str(7))
    def updateEightButton(self):
        self.updateCurrentCode(str(8))
    def updateNineButton(self):
        self.updateCurrentCode(str(9))
    def updateClearButton(self):
        self.clearCurrentCode()
    def updateEnterButton(self):
        self.enterCode()

        
    def enterCode(self):
        self.SCF(self.getCurrentCode())
        print("TODO: send code to microcontroller, return state of lock")
        
        
        
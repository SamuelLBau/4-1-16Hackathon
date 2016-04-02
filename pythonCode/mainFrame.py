import Tkinter as tk

from touchpadFrame import touchpadFrame as TPF


class mainFrame(tk.Frame):
    def __init__(self,master,telnet):
        self.WiFiCOM = telnet
        tk.Frame.__init__(self,master,bg='#F0F0F0')
        
        
        self.placeFrames()
        
    def placeFrames(self):
        print("TODO: Do stuff")
        self.touchpadFrame = TPF(self,self.WiFiCOM)
        
        
        
        
        
        self.touchpadFrame.grid(row=1,column=2)
import Tkinter as tk


class touchpadFrame(tk.Frame):
    def __init__(self,master,telnet):
        self.WiFiCOM = telnet
        tk.Frame.__init__(self,master,bg='#F0F0F0')
        
        
        self.placeFrames()
        
    def placeFrames(self):
        print("TODO: Create touchpad frame")
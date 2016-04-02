#!/usr/bin/env python
import Tkinter as tk

class getAdminPW(tk.Toplevel):
    def __init__(self,tryLogin=0):
        tk.Toplevel.__init__(self,bg='#F0F0F0')
        self.loginFunc = tryLogin
        self.title("Password selection")
        self.inputPWText = tk.Text(self,width=15,height=1,bd=0,bg='#F0F0F0')
        self.inputPWText.config(state='normal',width=len("Please input your administrator password"))
        self.inputPWText.delete(1.0, 'end')
        self.inputPWText.insert('insert',"Please input your administrator password")
        self.inputPWText.config(state='disable')
        
        self.inputPWTV = tk.StringVar()
        self.inputPWTV.trace("w", lambda name, index, mode, inputPWTV=self.inputPWTV.get(): self.empty())

        self.inputPWTB = tk.Entry(self,width = 30,textvariable=self.inputPWTV)
        
        
        self.enterButton = tk.Button(self,text="Enter",command=self.enterPW)
        
        
        self.inputPWText.grid(row=0,column=0,columnspan=2)
        self.inputPWTB.grid(row=1,column=0,columnspan=1,sticky="w")
        self.enterButton.grid(row=1,column=2,sticky="w")
        
    def enterPW(self):
        PW = self.inputPWTV.get()
        self.loginFunc(PW)
        self.destroy()
    def empty(self):
        num=1
            
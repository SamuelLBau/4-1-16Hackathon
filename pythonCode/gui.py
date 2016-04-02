import Tkinter as tk
from mainFrame import mainFrame



class Application(tk.Toplevel):

    def __init__(self,parent=None):
        tk.Toplevel.__init__(self,parent,bg='#F0F0F0',bd=1,relief='sunken')
        
        self.WiFiCOM = 1
        
        self.setupMenus()
        
        self.placeWidgets()
        
        
    def placeWidgets(self):
        self.mainFrame = mainFrame(self,self.WiFiCOM)
        
        
        self.mainFrame.grid()
        
    def setupMenus(self):
        self.menuBar = tk.Menu(self)
        
        self.adminMenu = tk.Menu(self.menuBar,tearoff=0)
        self.adminMenu.add_command(label="View Admin. Options",command=self.openAdminFrame)
        
        self.menuBar.add_cascade(label="Admin",menu=self.adminMenu)
        
        self.config(menu=self.menuBar)
        
        
    def openAdminFrame(self):
        print("TODO: Create admin password selection / change codes")
        
    
        
        
root = tk.Tk()
root.withdraw()
top = Application(root)
top.protocol("WM_DELETE_WINDOW", root.destroy)
top.title('Remote Safe')
root.mainloop()

import Tkinter as tk



class Application(tk.Toplevel):

    def __init__(self,parent=None):
        tk.Toplevel.__init__(self,parent,bg='#F0F0F0',bd=1,relief='sunken')
        
        self.placeWidgets()
        
        
    def placeWidgets(self):
        print("Place widgets here")
        
        
root = tk.Tk()
root.withdraw()
top = Application(root)
top.protocol("WM_DELETE_WINDOW", root.destroy)
top.title('Remote Safe')
root.mainloop()

import tkinter as tk
from tkinter import filedialog
import os

def RemoveExtension(s):
    s1=""
    for i in range(0, len(s)):
        if (s[i] != '.'):
            s1+=s[i]
        else:
            break
    return s1
    
class Notepad:

    def __init__(self, master):
        self.master = master
        self.filename = None

        # # Create line number text area
        # self.linenumbers = tk.Text(master, width=4, padx=3, pady=3, takefocus=0, border=0, background='lightgray',
        #                            state=tk.DISABLED)
        # self.linenumbers.pack(side=tk.LEFT, fill=tk.Y)

        #self.title=tk.title("Notepad")
        self.textarea = tk.Text(master, font=("Arial", 12))
        self.textarea.pack(fill=tk.BOTH, expand=True)

        #self.textarea.bind('<<Modified>>', self.update_line_numbers)

        self.create_menu()

    def create_menu(self):
        menubar = tk.Menu(self.master)
        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(label="New", command=self.new_file)
        filemenu.add_command(label="Open", command=self.open_file)
        filemenu.add_command(label="Save", command=self.save_file)
        filemenu.add_command(label="Save as", command=self.save_file_as)
        filemenu.add_command(label="Compile & Run", command=self.compile_run)
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=self.master.quit)
        menubar.add_cascade(label="File", menu=filemenu)
        self.master.config(menu=menubar)

    def new_file(self):
        self.textarea.delete("1.0", tk.END)
        self.filename = None

    def open_file(self):
        filetypes = (("Text files", "*.txt"), ("All files", "*.*"))
        filename = filedialog.askopenfilename(title="Open file", filetypes=filetypes)
        if filename:
            self.filename = filename
            with open(filename, "r") as f:
                self.textarea.delete("1.0", tk.END)
                self.textarea.insert(tk.END, f.read())

    def save_file(self):
        if not self.filename:
            self.filename = filedialog.asksaveasfilename(title="Save file", defaultextension=".txt",
                                                         filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
        if self.filename:
            with open(self.filename, "w") as f:
                f.write(self.textarea.get("1.0", tk.END))
    
    def save_file_as(self):
        self.filename = filedialog.asksaveasfilename(title="Save file", defaultextension=".txt",
                                                         filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
        if self.filename:
            with open(self.filename, "w") as f:
                f.write(self.textarea.get("1.0", tk.END))
    def compile_run(self):
        print("Compile & Run")
        filename=self.filename
        # print(filename)
        # print(RemoveExtension(filename)+".exe")
        
        os.system(".\\bbc.exe --g " + filename)
        file_cpp=RemoveExtension(filename)+".cpp"
        if (os.path.exists(file_cpp)):
            print("OK")
            os.remove(file_cpp)
            os.system(".\\bbc.exe "+filename)
            file_exe=RemoveExtension(filename)+".exe"
            if (os.path.exists(file_exe)):
                os.system(file_exe)


        # if (os.path.exists(file_exe)):
        #     os.remove(file_exe)
        # #print(filename)
        # os.system(".\\bbc.exe "+filename)
        # file_exe=RemoveExtension(filename)+".exe"
        # if (os.path.exists(file_exe)):
        #     os.startfile(file_exe)
        
    # def update_line_numbers(self, event=None):
    #     lines = str(self.textarea.get(1.0, tk.END)).count('\n')
    #     line_numbers_text = '\n'.join(str(i) for i in range(1, lines + 2))
    #     self.linenumbers.config(state=tk.NORMAL)
    #     self.linenumbers.delete(1.0, tk.END)
    #     self.linenumbers.insert(tk.END, line_numbers_text)
    #     self.linenumbers.config(state=tk.DISABLED)

root = tk.Tk()
root.title("Barebone Compiler")
notepad = Notepad(root)

root.mainloop()

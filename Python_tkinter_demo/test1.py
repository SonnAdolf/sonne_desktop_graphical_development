#!/usr/bin/python3

from Tkinter import *
import os
import tkFileDialog as filedialog
import zipfile

def unzip(zipFilePath, destDir):
    zfile = zipfile.ZipFile(zipFilePath)
    for name in zfile.namelist():
        (dirName, fileName) = os.path.split(name)
        if fileName == '':
            # directory
            newDir = destDir + '/' + dirName
            if not os.path.exists(newDir):
                os.mkdir(newDir)
        else:
            # file
            fd = open(destDir + '/' + name, 'wb')
            fd.write(zfile.read(name))
            fd.close()
    zfile.close()

def choose_directory():
	dirctory_choosen = filedialog.askdirectory(initialdir='C:')
	# unzip my program to directory choosen
	dirctory_choosen = dirctory_choosen + '/tg_software'
	if not os.path.exists(dirctory_choosen):
		os.makedirs(dirctory_choosen)
	entryText.set(dirctory_choosen)
	unzip('tgsoftware.zip',dirctory_choosen)

def next():
   # fisrt of all get the values of entry widgets
   str_url = db_url_entry.get()
   str_usrname = db_usrname_entry.get()
   str_passwd = db_password_entry.get()
   # for reseting the window delete labels and entry widgets and button
   db_url_label.destroy()
   db_usrname_label.destroy()
   db_passwd_label.destroy()
   db_url_entry.destroy()
   db_usrname_entry.destroy()
   db_password_entry.destroy()
   b2.destroy()
   global file_label
   file_label = Label(master, text="hhhh")
   file_label.grid(row=0)
   global entryText
   entryText = StringVar()
   global file_entry
   file_entry = Entry(master,textvariable=entryText)
   file_entry.grid(row=0, column=1)
   global file_btn
   file_btn = Button(master, text='Choose directory', command=choose_directory)
   b1.grid(row=1,column=0)
   file_btn.grid(row=0,column=2)

global master
master = Tk()
global db_url_label
db_url_label = Label(master, text="Database url")
db_url_label.grid(row=0)
global db_usrname_label
db_usrname_label = Label(master, text="Database username")
db_usrname_label.grid(row=1)
global db_passwd_label
db_passwd_label = Label(master, text="Database password")
db_passwd_label.grid(row=2)

global db_url_entry
db_url_entry = Entry(master)
global db_usrname_entry
db_usrname_entry = Entry(master)
global db_password_entry
db_password_entry = Entry(master)

db_url_entry.grid(row=0, column=1)
db_usrname_entry.grid(row=1, column=1)
db_password_entry.grid(row=2, column=1)

global b1
b1 = Button(master, text='Quit', command=master.quit)
b1.grid(row=4, column=0, sticky=W, pady=4)
global b2
b2 = Button(master, text='Next', command=next)
b2.grid(row=4, column=1, sticky=W, pady=4)

mainloop()
	
	


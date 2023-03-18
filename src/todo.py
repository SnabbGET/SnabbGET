#!/usr/bin/python

import tkinter
import random
import os

MAX_LINE_NUM = 0
MAX_FILE_NUM = 0
MAX_TEXT_NUM = 0

w = "TOD"+"O" # Avoid to have this line in the resuls

def lstdir(d, r = []):
	global MAX_LINE_NUM
	global MAX_FILE_NUM
	global MAX_TEXT_NUM
	for f2 in os.listdir(d):
		p = os.path.join(d, f2)
	#	print(p)
		if os.path.isfile(p):
			try:
				with open(p, 'r') as f:
					ls = f.readlines()
					for l in ls:
						if l.find(w) != -1:
							try:
								if os.path.basename(p).find(".py") == -1\
										and os.path.basename(p) != "Makefile":
									t = l.split("//")
									t.pop(0)
									t = ''.join(t)
									t = t.split("\n")
									t = t[0]
									if t.__len__() == 0:
										t = l
									#print(f.name, "\033[35m@", ls.index(l)+1,
									#	":\033[33m" + ''.join(t), end="\033[0m")
									r += [{"line": ls.index(l)+1, 
										   "file": f.name,
										   "text": t}]
									if str(ls.index(l) + 1).__len__() > MAX_LINE_NUM:
										MAX_LINE_NUM = str(ls.index(l)+1).__len__()
									if f.name.__len__() > MAX_FILE_NUM:
										MAX_FILE_NUM = f.name.__len__()
									if t.__len__() > MAX_TEXT_NUM:
										MAX_TEXT_NUM = t.__len__()
								else:
									t = l.split("#")
									t.pop(0)
									t = ''.join(t)
									t = t.split("\n")
									t = t[0]
									if t.__len__() == 0:
										t = l
									#print(f.name, "\033[35m@", ls.index(l)+1,
									#	":\033[33m"+''.join(t), end="\033[0m")
									r += [{"line": ls.index(l)+1, 
										   "file": f.name,
										   "text": t}]
									if str(ls.index(l) + 1).__len__() > MAX_LINE_NUM:
										MAX_LINE_NUM = str(ls.index(l)+1).__len__()
									if f.name.__len__() > MAX_FILE_NUM:
										MAX_FILE_NUM = f.name.__len__()
									if t.__len__() > MAX_TEXT_NUM:
										MAX_TEXT_NUM = t.__len__()
							except IndexError:
							#	print(f.name, "\033[35m@", ls.index(l),
							#		":\033[33m", l, end="\033[0m")
								t = l.split("\n")
								t = t[0]
								r += [{"line": ls.index(l), 
									   "file": f.name,
									   "text": t}]
								if str(ls.index(l) + 1).__len__() > MAX_LINE_NUM:
									MAX_LINE_NUM = str(ls.index(l)).__len__()
								if f.name.__len__() > MAX_FILE_NUM:
									MAX_FILE_NUM = f.name.__len__()
								if t.__len__() > MAX_TEXT_NUM:
									MAX_TEXT_NUM = t.__len__()
			except UnicodeDecodeError:
				pass
		elif os.path.isdir(p) and os.path.basename(p) != ".git":
		#	print("Cd in", os.path.basename(p))
			lstdir(p, r)
	return r

def todos():
	"""Test function"""
	global MAX_LINE_NUM
	global MAX_FILE_NUM
	global MAX_TEXT_NUM
	r = []
	for i in range(50):
		l = random.randint(0, 500)
		f = "c:/jrggr"
		t = "todo" + str(i)
		if str(l).__len__() > MAX_LINE_NUM:
			MAX_LINE_NUM = str(l).__len__()
		if f.__len__() > MAX_FILE_NUM:
			MAX_FILE_NUM = f.__len__()
		if t.__len__() > MAX_TEXT_NUM:
			MAX_TEXT_NUM = t.__len__()
		r += [{"line" : l, "file" : f, "text" : t}]
	return r

#lstdir("./src")

t = lstdir("./src")
print(t, MAX_LINE_NUM, MAX_TEXT_NUM, MAX_FILE_NUM)
f = tkinter.Tk()
f.title("ToDo")

j = 0
for i in t:
	while str(i["line"]).__len__() < MAX_LINE_NUM:
		i["line"] = " " + str(i["line"])
	t = tkinter.Label(f, text=i["line"], bg="magenta", font="consolas")
	j+=1
	t.grid(row=j, column=0)
	while i["file"].__len__() < MAX_FILE_NUM:
		i["file"] = " " + i["file"]
	t = tkinter.Label(f, text=i["file"], bg="lime", font="consolas")
	t.grid(row=j, column=10)
	while i["text"].__len__() < MAX_TEXT_NUM:
		i["text"] = " " + i["text"]
	t = tkinter.Label(f, text=i["text"], bg="aqua", font="consolas")
	t.grid(row=j, column=200)

f.mainloop()


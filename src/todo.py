#!/usr/bin/python

import tkinter
import random
import os

MAX_LINE_NUM = 0
MAX_FILE_NUM = 0
MAX_TEXT_NUM = 0

TO_DO_WORD = "TOD"+"O" # Avoid to have this line in the resuls

def read_file(p, line_in_f, ALL_LINES):
	global MAX_LINE_NUM
	global MAX_FILE_NUM
	global MAX_TEXT_NUM
	"""Read the file (haha)"""
	if os.path.basename(p).find(".py") == -1\
			and os.path.basename(p) != "Makefile":
		to_do_text = line_in_f.split("//")
		to_do_text.pop(0)
		to_do_text = ''.join(to_do_text)
		to_do_text = to_do_text.split("\n")
		to_do_text = to_do_text[0]
		if to_do_text.__len__() == 0:
			to_do_text = line_in_f
		#print(FILE_IN_D.name, "\033[35m@", ALL_LINES.index(line_in_f)+1,
		#	":\033[33m" + ''.join(to_do_text), end="\033[0m")
		dico_all_td += [{"line": ALL_LINES.index(line_in_f)+1,
				"file": FILE_IN_D.name,
				"text": to_do_text}]
		if str(ALL_LINES.index(line_in_f) + 1).__len__() > MAX_LINE_NUM:
			MAX_LINE_NUM = str(ALL_LINES.index(line_in_f)+1).__len__()
		if FILE_IN_D.name.__len__() > MAX_FILE_NUM:
			MAX_FILE_NUM = FILE_IN_D.name.__len__()
		if to_do_text.__len__() > MAX_TEXT_NUM:
			MAX_TEXT_NUM = to_do_text.__len__()
	else:
		to_do_text = line_in_f.split("#")
		to_do_text.pop(0)
		to_do_text = ''.join(to_do_text)
		to_do_text = to_do_text.split("\n")
		to_do_text = to_do_text[0]
		if to_do_text.__len__() == 0:
			to_do_text = line_in_f
		#print(FILE_IN_D.name, "\033[35m@", ALL_LINES.index(line_in_f)+1,
		#	":\033[33m"+''.join(to_do_text), end="\033[0m")
		dico_all_td += [{"line": ALL_LINES.index(line_in_f)+1,
				"file": FILE_IN_D.name,
				"text": to_do_text}]
		if str(ALL_LINES.index(line_in_f) + 1).__len__() > MAX_LINE_NUM:
			MAX_LINE_NUM = str(ALL_LINES.index(line_in_f)+1).__len__()
		if FILE_IN_D.name.__len__() > MAX_FILE_NUM:
			MAX_FILE_NUM = FILE_IN_D.name.__len__()
		if to_do_text.__len__() > MAX_TEXT_NUM:
			MAX_TEXT_NUM = to_do_text.__len__()
	return dico_all_td

def lstdir(d, dico_all_td=[]):
	"""
	List the files in all folders.
	"""
	global MAX_LINE_NUM
	global MAX_FILE_NUM
	global MAX_TEXT_NUM
	for f2 in os.listdir(d):
		p = os.path.join(d, f2)
	#	print(p)
		if os.path.isfile(p):
			try:
				with open(p, 'r') as FILE_IN_D:
					ALL_LINES = FILE_IN_D.readlines()
					for line_in_f in ALL_LINES:
						if line_in_f.find(TO_DO_WORD) != -1:
							try:
								dico_all_td = read_file(p, line_in_f, ALL_LINES)
							except IndexError:
							#	print(FILE_IN_D.name, "\033[35m@", ALL_LINES.index(line_in_f),
							#		":\033[33m", line_in_f, end="\033[0m")
								to_do_text = line_in_f.split("\n")
								to_do_text = to_do_text[0]
								dico_all_td += [{"line": ALL_LINES.index(line_in_f),
										"file": FILE_IN_D.name,
										"text": to_do_text}]
								if str(ALL_LINES.index(line_in_f) + 1).__len__() > MAX_LINE_NUM:
									MAX_LINE_NUM = str(ALL_LINES.index(line_in_f)).__len__()
								if FILE_IN_D.name.__len__() > MAX_FILE_NUM:
									MAX_FILE_NUM = FILE_IN_D.name.__len__()
								if to_do_text.__len__() > MAX_TEXT_NUM:
									MAX_TEXT_NUM = to_do_text.__len__()
			except UnicodeDecodeError:
				pass
		elif os.path.isdir(p) and os.path.basename(p) != ".git":
		#	print("Cd in", os.path.basename(p))
			lstdir(p, dico_all_td)
	return dico_all_td

def todos():
	"""Test function"""
	global MAX_LINE_NUM
	global MAX_FILE_NUM
	global MAX_TEXT_NUM
	dico_all_td = []
	for i in range(50):
		line_in_f = random.randint(0, 500)
		FILE_IN_D = "c:/jrggr"
		to_do_text = "todo" + str(i)
		if str(line_in_f).__len__() > MAX_LINE_NUM:
			MAX_LINE_NUM = str(line_in_f).__len__()
		if FILE_IN_D.__len__() > MAX_FILE_NUM:
			MAX_FILE_NUM = FILE_IN_D.__len__()
		if to_do_text.__len__() > MAX_TEXT_NUM:
			MAX_TEXT_NUM = to_do_text.__len__()
		dico_all_td += [{"line" : line_in_f, "file" : FILE_IN_D, "text" : to_do_text}]
	return dico_all_td

#lstdir("./src")

to_do_text = lstdir("./src")
print(to_do_text, MAX_LINE_NUM, MAX_TEXT_NUM, MAX_FILE_NUM)
FILE_IN_D = tkinter.Tk()
FILE_IN_D.title("ToDo")

j = 0
for i in to_do_text:
	while str(i["line"]).__len__() < MAX_LINE_NUM:
		i["line"] = " " + str(i["line"])
	to_do_text = tkinter.Label(FILE_IN_D, text=i["line"], bg="magenta", font="consolas")
	j += 1
	to_do_text.grid(row=j, column=0)
	while i["file"].__len__() < MAX_FILE_NUM:
		i["file"] = " " + i["file"]
	to_do_text = tkinter.Label(FILE_IN_D, text=i["file"], bg="lime", font="consolas")
	to_do_text.grid(row=j, column=10)
	while i["text"].__len__() < MAX_TEXT_NUM:
		i["text"] = " " + i["text"]
	to_do_text = tkinter.Label(FILE_IN_D, text=i["text"], bg="aqua", font="consolas")
	to_do_text.grid(row=j, column=200)

FILE_IN_D.mainloop()

#!/usr/bin/python

import tkinter
import random
import os

MAX_LINE_NUM = 0
MAX_FILE_NUM = 0
MAX_TEXT_NUM = 0

TO_DO_WORD = "TOD"+"O" # Avoid to have this line in the resuls

def read_file(p, line_in_f, all_lines, dico_all_td, file_in_d):
    """Read the file (haha)"""

    global MAX_LINE_NUM
    global MAX_FILE_NUM
    global MAX_TEXT_NUM
    if os.path.basename(p).find(".py") == -1\
            and os.path.basename(p) != "Makefile":
        to_do_text = line_in_f.split("//")
        to_do_text.pop(0)
        to_do_text = ''.join(to_do_text)
        to_do_text = to_do_text.split("\n")
        to_do_text = to_do_text[0]
        if len(to_do_text) == 0:
            to_do_text = line_in_f
        #print(file_in_d.name, "\033[35m@", all_lines.index(line_in_f)+1,
        #    ":\033[33m" + ''.join(to_do_text), end="\033[0m")
        dico_all_td += [{"line": all_lines.index(line_in_f)+1,
                "file": file_in_d.name,
                "text": to_do_text}]
        if len(str(all_lines.index(line_in_f) + 1)) > MAX_LINE_NUM:
            MAX_LINE_NUM = len(str(all_lines.index(line_in_f)+1))
        if len(file_in_d.name) > MAX_FILE_NUM:
            MAX_FILE_NUM = len(file_in_d.name)
        if len(to_do_text) > MAX_TEXT_NUM:
            MAX_TEXT_NUM = len(to_do_text)
    else:
        to_do_text = line_in_f.split("#")
        to_do_text.pop(0)
        to_do_text = ''.join(to_do_text)
        to_do_text = to_do_text.split("\n")
        to_do_text = to_do_text[0]
        if len(to_do_text) == 0:
            to_do_text = line_in_f
        #print(file_in_d.name, "\033[35m@", all_lines.index(line_in_f)+1,
        #    ":\033[33m"+''.join(to_do_text), end="\033[0m")
        dico_all_td += [{"line": all_lines.index(line_in_f)+1,
                "file": file_in_d.name,
                "text": to_do_text}]
        if len(str(all_lines.index(line_in_f) + 1)) > MAX_LINE_NUM:
            MAX_LINE_NUM = len(str(all_lines.index(line_in_f)+1))
        if len(file_in_d.name) > MAX_FILE_NUM:
            MAX_FILE_NUM = len(file_in_d.name)
        if len(to_do_text) > MAX_TEXT_NUM:
            MAX_TEXT_NUM = len(to_do_text)
    return dico_all_td

def lstdir(d, dico_all_td=[]):
    """
    List the files in all folders.
    """
    global MAX_LINE_NUM
    global MAX_FILE_NUM
    global MAX_TEXT_NUM
    for f_2 in os.listdir(d):
        p = os.path.join(d, f_2)
    #    print(p)
        if os.path.isfile(p):
            try:
                with open(p, 'r', -1, 'UTF-8') as file_in_d:
                    all_lines = file_in_d.readlines()
                    for line_in_f in all_lines:
                        if line_in_f.find(TO_DO_WORD) != -1:
                            try:
                                dico_all_td = read_file(p, line_in_f, all_lines, dico_all_td, file_in_d)
                            except IndexError:
                                #print(file_in_d.name, "\033[35m@", all_lines.index(line_in_f),
                                #":\033[33m", line_in_f, end="\033[0m")
                                to_do_text = line_in_f.split("\n")
                                to_do_text = to_do_text[0]
                                dico_all_td += [{"line": all_lines.index(line_in_f),
                                        "file": file_in_d.name,
                                        "text": to_do_text}]
                                if len(str(all_lines.index(line_in_f) + 1)) > MAX_LINE_NUM:
                                    MAX_LINE_NUM = len(str(all_lines.index(line_in_f)))
                                if len(file_in_d) > MAX_FILE_NUM:
                                    MAX_FILE_NUM = len(file_in_d.name)
                                if len(to_do_text) > MAX_TEXT_NUM:
                                    MAX_TEXT_NUM = len(to_do_text)
            except UnicodeDecodeError:
                pass
        elif os.path.isdir(p) and os.path.basename(p) != ".git":
            #print("Cd in", os.path.basename(p))
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
        file_in_d = "c:/jrggr"
        to_do_text = "todo" + str(i)
        if len(str(line_in_f)) > MAX_LINE_NUM:
            MAX_LINE_NUM = len(str(line_in_f))
        if len(file_in_d) > MAX_FILE_NUM:
            MAX_FILE_NUM = len(file_in_d)
        if len(to_do_text) > MAX_TEXT_NUM:
            MAX_TEXT_NUM = len(to_do_text)
        dico_all_td += [{"line" : line_in_f, "file" : file_in_d, "text" : to_do_text}]
    return dico_all_td

#lstdir("./src")


to_do_text = lstdir("./")
print(to_do_text, MAX_LINE_NUM, MAX_TEXT_NUM, MAX_FILE_NUM)
file_in_d = tkinter.Tk()
file_in_d.title("ToDo")

j = 0
for i in to_do_text:
    while len(str(i["line"])) < MAX_LINE_NUM:
        i["line"] = " " + str(i["line"])
    to_do_text = tkinter.Label(file_in_d, text=i["line"], bg="magenta", font="consolas")
    j += 1
    to_do_text.grid(row=j, column=0)
    while len(i["file"]) < MAX_FILE_NUM:
        i["file"] = " " + i["file"]
    to_do_text = tkinter.Label(file_in_d, text=i["file"], bg="lime", font="consolas")
    to_do_text.grid(row=j, column=10)
    while len(i["text"]) < MAX_TEXT_NUM:
        i["text"] = " " + i["text"]
    to_do_text = tkinter.Label(file_in_d, text=i["text"], bg="aqua", font="consolas")
    to_do_text.grid(row=j, column=200)

file_in_d.mainloop()

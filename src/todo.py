import os

w = "TOD"+"O" # Avoid to have this line in the resuls

def lstdir(d):
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
									if t.__len__() == 0:
										t = l
									print(f.name, "\033[35m@", ls.index(l)+1,
										":\033[33m" + ''.join(t), end="\033[0m")
								else:
									t = l.split("#")
									t.pop(0)
									if t.__len__() == 0:
										t = l
									print(f.name, "\033[35m@", ls.index(l)+1,
										":\033[33m"+''.join(t), end="\033[0m")
							except IndexError:
								print(f.name, "\033[35m@", ls.index(l),
									":\033[33m", l, end="\033[0m")
			except UnicodeDecodeError:
				pass
		elif os.path.isdir(p) and os.path.basename(p) != ".git":
		#	print("Cd in", os.path.basename(p))
			lstdir(p)

lstdir("./src")

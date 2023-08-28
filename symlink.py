#!/bin/python3

import os
import shutil

CREATE_SYMLINKS = True # Set false to copy files at the symbolic link path
					   # (useful on FAT32 devives)
# NOTE: Admin rights or Windows Dev mode must be enabled
# To start this file as admin, you can type in powershell:
# Start-Process -Verb RunAs cmd.exe -Args '/c', "python symlink.py & pause"

os.chdir("./include")

SYMLINKS_PATHS = [
    os.path.join(dirpath,f)	for (dirpath, dirnames, filenames) in 
        os.walk("./") for f in filenames]

for path in SYMLINKS_PATHS:
	os.chdir(os.path.dirname(path))

	src_file_path = os.open(os.path.basename(path), os.O_RDONLY)
	src_file_txt = os.read(
						src_file_path,
						os.path.getsize(src_file_path)
					).decode('utf-8')
	if os.name == 'nt':
		src_file_txt = src_file_txt.replace("/", "\\")
	print("Path:", src_file_path, "; SrcFile:", src_file_txt)
	os.close(src_file_path)

	if os.path.isfile(os.path.basename(path)):
		os.remove(os.path.basename(path))
		if CREATE_SYMLINKS:
			os.symlink(src_file_txt, os.path.basename(path), False)
		else:
			shutil.copy2(src_file_txt, path)

	os.chdir("../")

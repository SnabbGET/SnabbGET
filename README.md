# SnabbGET

Graphic and fast terminal in C/C++.

## Compile

To use the termial version:

```bash
g++ src/*.cpp src/core/*.cpp -o "output"
# if it doesn't works, try:
g++ -D FILEENUMERR src/main.cpp -o "output"

./output
```

To debug use:

```bash
g++ -Wall -D DEBUG -g3 src/*.cpp src/core/*.cpp -o "output"
# if it doesn't works, try:
g++ -Wall -D FILEENUMERR -D DEBUG -g3 src/main.cpp -o "output"

gdb ./output
```

To use the GUI version (in dev), you must have [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) installed:

```bash
g++ -c src/interface/gui.cpp
g++ gui.o -o gui -lsfml-graphics -lsfml-window -lsfml-system
./gui
```

# SnabbGET

Graphic and fast terminal in C/C++.

v0.0.1

## Compile

Use the termial version (CLI):

```bash
make
./output
```

Debug:

```bash
make
make run
```

To use the GUI version (in dev), you must have [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) installed:

```bash
g++ -c src/interface/gui.cpp
g++ gui.o -o gui -lsfml-graphics -lsfml-window -lsfml-system
./gui
```

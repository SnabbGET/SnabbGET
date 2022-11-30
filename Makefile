filename = output
DEBUG = on
arg =
wasm = off

.PHONY: all pre-compile compile gui

all: pre-compile compile

pre_compile:
	@echo "Pre-generating..."
	g++ src/core/gen/includes_files.cpp -o "includes" -std=c++1z
	./includes

compile: pre_compile
	@echo "Generating..."
ifeq (${DEBUG}, on)
	g++ -Wall -Wextra -D DEBUG -O3 -g3 src/*.cpp src/core/utils.cpp -o \
	"${filename}" -std=c++1z
else
	g++ -Wall -Wextra -O3 -g3 src/*.cpp src/core/utils.cpp -o \
	"${filename}" -std=c++1z
endif
ifneq (${wasm}, off)
	em++ -D DEBUG src/*.cpp src/core/utils.cpp -o \
	"web/${filename}.html" --shell-file\
	html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s \
	"EXPORTED_RUNTIME_METHODS=['ccall']" -std=c++1z
endif

run: all
	@echo "Starting..."
ifeq (${wasm}, off)
ifeq (${DEBUG}, on)
	gdb ${filename} ${arg}
else
	./${filename} ${arg}
endif
else
	@echo "The web page is available on web/${filename}.html"
endif

gui:
	@echo "Generating the gui..."
	cd src/interface && javac gui.java
	g++ -D _FORJAVAGUI_ src/*.cpp src/core/utils.cpp -std=c++1z -o \
	"src/interface/prompt"

runGui: gui
	@echo "Running the gui..."
	cd src/interface && java editor

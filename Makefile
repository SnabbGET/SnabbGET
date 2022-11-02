filename = output
DEBUG = on
arg =
wasm = off

.PHONY: all pre-compile compile execute

all: pre-compile compile

pre_compile:
	@echo "Pre-generating..."
	g++ src/core/gen/includes_files.cpp -o "includes" && ./includes

compile: pre_compile
	@echo "Generating..."
ifeq (${DEBUG}, on)
	g++ -Wall -Wextra -D DEBUG -g3 src/*.cpp src/core/utils.cpp -o "${filename}"
else
	g++ -Wall -Wextra -g3 src/*.cpp src/core/utils.cpp -o "${filename}"
endif
ifneq (${wasm}, off)
	em++ -D DEBUG src/*.cpp src/core/utils.cpp -o "web/${filename}.html" --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"
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
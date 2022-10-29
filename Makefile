filename = output
DEBUG = on
arg =

.PHONY: all pre-compile compile execute

all: pre-compile compile

pre-compile:
	@echo "Pre-generating..."
	g++ src/core/gen/includes_files.cpp -o "includes" && ./includes

compile: includes
	@echo "Generating..."
ifeq (${DEBUG}, on)
	g++ -Wall -Wextra -D DEBUG -g3 src/*.cpp src/core/utils.cpp -o "${filename}"
else
	g++ -Wall -Wextra -g3 src/*.cpp src/core/utils.cpp -o "${filename}"
endif

run: ${filename}
	@echo "Starting..."
ifeq (${DEBUG}, on)
	gdb ${filename} ${arg}
else
	./${filename} ${arg}
endif

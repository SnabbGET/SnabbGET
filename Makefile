filename = output
DEBUG = on
arg =
wasm = off

GCC = g++
EMCC = em++
GDB = gdb
CD = cd
MAKE = make
JAVA = java
JAVAC = javac

.PHONY: all compile_cmds compile_utils compile_shell link gui libs

all: compile_cmds compile_utils compile_shell compile_main link

first_time: libs compile_cmds compile_utils compile_shell compile_main link

compile_cmds: ./src/core/cmd/*.cpp
	@for file in $^ ; do \
		echo "Compiling $${file}..." ;\
		${GCC} -Wall -Wextra -D DEBUG -O3 -g3 $${file} -o \
		"$${file}.o" -c -std=c++1z -L./libs/readline-8.2 -lreadline \
		-lhistory -ltinfo;\
	done

compile_utils:
	@echo "Compiling utils.cpp..."
	@${GCC} -Wall -Wextra -D DEBUG -O3 -g3 src/core/utils.cpp -o \
	"utils.o" -c -std=c++1z -L./libs/readline-8.2 -lreadline \
	-lhistory -ltinfo
#	g++ src/core/gen/includes_files.cpp -o "includes" -std=c++1z
#	./includes

compile_shell:
	@echo "Compiling shell.cpp"
	@${GCC} -Wall -Wextra -D DEBUG -O3 -g3 src/core/shell.cpp -o \
	"shell.o" -c -std=c++1z -L./libs/readline-8.2 -lreadline \
	-lhistory -ltinfo

compile_main:
	@echo "Compiling main.cpp"
	@${GCC} -Wall -Wextra -D DEBUG -O3 -g3 src/main.cpp -o \
	"main.o" -c -std=c++1z -L./libs/readline-8.2 -lreadline \
	-lhistory -ltinfo

link: ./src/core/cmd/*.cpp.o
	@echo "Generating..."
ifeq (${DEBUG}, on)
	@${GCC} -Wall -Wextra -O3 -g3 ./utils.o ./shell.o ./main.o $^ -o \
	"${filename}" -std=c++1z -L./libs/readline-8.2 -lreadline \
	-lhistory -ltinfo
else
	@${GCC} -Wall -Wextra -O3 -g3 src/*.cpp src/core/utils.cpp -o \
	"${filename}" -std=c++1z -L./libs/readline-8.2 -lreadline \
	-lhistory -ltinfo
endif
ifneq (${wasm}, off)
	@${EMCC} -D DEBUG src/*.cpp src/core/utils.cpp -o \
	"web/${filename}.html" --shell-file \
	html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s \
	"EXPORTED_RUNTIME_METHODS=['ccall']" -std=c++1z \
	-L./libs/readline-8.2 -lreadline -lhistory
endif

# Compile libs
libs: # TODO: Windows       |---------v
	@${CD} libs/readline-8.2 && ./configure && ${MAKE} && ${CD} ../../
#	cd libs/exprtk-master && g++ exprtk.hpp -pedantic-errors -Wall -Wextra \
#	-Werror -Wno-long-long -O3 && cd ../../
#	cp libs/exprtk-master/exprtk.hpp.gch include/exprtk/

run: all
	@echo "Starting..."
ifeq (${wasm}, off)
ifeq (${DEBUG}, on)
	${GDB} ${filename} ${arg}
else
	./${filename} ${arg}
endif
else
	@echo "The web page is available on web/${filename}.html"
endif

gui:
	@echo "Generating the gui..."
	${CD} src/interface && ${JAVAC} Gui.java
	${GCC} -D _FORJAVAGUI_ src/*.cpp src/core/utils.cpp -std=c++1z -o \
	"src/interface/prompt"

runGui: gui
	@echo "Running the gui..."
	${CD} src/interface && ${JAVA} editor

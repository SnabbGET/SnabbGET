filename = output
DEBUG = on
arg = -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough
readline_arg = -L./libs/readline-8.2 -lreadline -lhistory -ltinfo
wasm = off

cmd_files = ./src/core/cmd/*.cpp

CC = g++
EMCC = em++
GDB = gdb
CD = cd
MAKE = make
JAVA = java
JAVAC = javac

.PHONY: all $(cmd_files) compile_utils compile_shell compile_main compile_chatbox link gui libs link_for_chatbox

all: $(cmd_files) compile_utils compile_shell compile_main link

chatbox: $(cmd_files) compile_utils compile_shell compile_chatbox link_for_chatbox
	readline_arg=-D NO_RL

first_time: libs $(cmd_files) compile_utils compile_shell compile_main link

$(cmd_files): %:
	@echo "Compiling $@..."
	@${CC} -D DEBUG $@ -o "$@.o" -c ${arg} ${readline_arg}

compile_utils:
	@echo "Compiling utils.cpp..."
	@${CC} -D DEBUG src/core/utils.cpp -o "utils.o" -c ${arg} ${readline_arg}
#	g++ src/core/gen/includes_files.cpp -o "includes" -std=c++1z
#	./includes

compile_shell:
	@echo "Compiling shell.cpp"
	@${CC} -D DEBUG src/core/shell.cpp -o "shell.o" -c ${arg} ${readline_arg}
compile_main:
	@echo "Compiling main.cpp"
	@${CC} -D DEBUG src/main.cpp -o "main.o" -c ${arg} ${readline_arg}

compile_chatbox:
	@echo "Compiling chatbox.cpp"
	@${CC} -D DEBUG src/chat/chatbox.cpp -o "chatbox.o" -c ${arg}

link: ./src/core/cmd/*.cpp.o
	@echo "Generating..."
	@echo "If you have an error like 'ld: cannot find -ltinfo', install the 'libncurses-dev' package."
ifeq (${DEBUG}, on)
	@${CC} ./utils.o ./shell.o ./main.o $^ -o "${filename}" ${arg}
else
	@${CC} src/*.cpp src/core/utils.cpp -o "${filename}" ${arg}
#	TODO: change in all compilations the '-D DEBUG': use that only if the user wants
#	(add ifeq (${DEBUG}, on))
endif
ifneq (${wasm}, off)
	@${EMCC} -D DEBUG src/*.cpp src/core/utils.cpp -o \
	"web/${filename}.html" --shell-file \
	html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s \
	"EXPORTED_RUNTIME_METHODS=['ccall']" ${arg}
endif

link_for_chatbox:
	@echo "Generating..."
	${CC} ./utils.o ./shell.o ./chatbox.o ./src/core/cmd/*.cpp.o -o "${filename}_chatbox" ${arg}

lib_readline:
	@echo "Precompiling Readline..."
	@${CD} libs/readline-8.2 && ./configure && ${MAKE} && ${CD} ../../

lib_exprtk:
	@echo "Precompiling exprtk..."
	@${CC} "include/exprtk/exprtk.hpp" -o "include/exprtk/exprtk.hpp.gch" -c ${arg}

# Compile libs
libs: lib_readline lib_exprtk

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
	${CC} -D _FORJAVAGUI_ src/*.cpp src/core/utils.cpp -std=c++1z -o \
	"src/interface/prompt"

runGui: gui
	@echo "Running the gui..."
	${CD} src/interface && ${JAVA} editor

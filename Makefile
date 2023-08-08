filename = output
DEBUG = on

# Add -Wa,-mbig-obj if you can
arg = -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough -Wno-unused-result
isocline_arg =
wasm = off

ifeq ($(OS),Windows_NT)
	o_ext = obj
else
	o_ext = o
endif

cmd_files = ./src/core/cmd/*.cpp

CC = g++
EMCC = em++
GDB = gdb
CD = cd
MAKE = make
JAVA = java
JAVAC = javac

.PHONY: all $(cmd_files) compile_cmd compile_utils compile_shell compile_main compile_chatbox link gui libs link_for_chatbox

all: compile_utils compile_shell compile_main link

chatbox: isocline_arg=-D NO_RL
chatbox: $(cmd_files) compile_utils compile_shell compile_chatbox link_for_chatbox

first_time: libs $(cmd_files) compile_utils compile_shell compile_main link

compile_cmd: $(cmd_files)

$(cmd_files): %:
	@echo "Compiling $@..."
	@${CC} -D DEBUG $@ -o "./$@.${o_ext}" -c ${arg} ${isocline_arg}

compile_utils:
	@echo "Compiling utils.cpp..."
	@${CC} -D DEBUG ./src/core/utils.cpp -o "./utils.${o_ext}" -c ${arg} ${isocline_arg}
#	g++ ./src/core/gen/includes_files.cpp -o "includes" -std=c++1z
#	./includes

compile_shell:
	@echo "Compiling shell.cpp..."
	@${CC} -D DEBUG ./src/core/shell.cpp -o "./shell.${o_ext}" -c ${arg} ${isocline_arg}
compile_main:
	@echo "Compiling main.cpp..."
	@${CC} -D DEBUG ./src/main.cpp -o "./main.${o_ext}" -c ${arg} ${isocline_arg}

compile_chatbox:
	@echo "Compiling chatbox.cpp..."
	@${CC} -D DEBUG ./src/chat/chatbox.cpp -o "./chatbox.${o_ext}" -c ${arg}

link_for_chatbox:
	@echo "Generating..."
	${CC} ./utils.${o_ext} ./shell.${o_ext} ./chatbox.${o_ext} ./src/core/cmd/*.cpp.${o_ext} -o "./${filename}_chatbox" ${arg}

link: $(cmd_files).${o_ext}
	@echo "Generating..."
	@${CC} ./utils.${o_ext} ./shell.${o_ext} ./main.${o_ext} ./isocline.${o_ext} $^ -o "./${filename}" ${arg}
#	TODO: change in all compilations the '-D DEBUG': use that only if the user wants
#	(add ifeq (${DEBUG}, on))
ifneq (${wasm}, off)
	@${EMCC} -D DEBUG src/*.cpp src/core/utils.cpp -o \
	"web/${filename}.html" --shell-file \
	html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s \
	"EXPORTED_RUNTIME_METHODS=['ccall']" ${arg}
endif

lib_exprtk:
	@echo "Precompiling exprtk..."
	@${CC} "./include/exprtk/exprtk.hpp" -o "./include/exprtk/exprtk.hpp.gch" -c ${arg}

lib_isoline:
	@echo "Compiling Isocline..."
	@${CC} ./libs/isocline/src/isocline.c -o "./isocline.${o_ext}" -c ${arg}

# Compile libs
libs: lib_exprtk lib_isoline

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

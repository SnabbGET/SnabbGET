:: FOR MINGW USERS: USE Make.sh GCC COMMANDS!

cl.exe "include/exprtk/exprtk.hpp" /Fp "include/exprtk/exprtk.hpp.gch" -c /bigobj /W4 /O2 /std:c++17
for /f %f in ('dir /b src/core/cmds') do cl.exe /D DEBUG %f /Fi %f.o -c /bigobj /W4 /O2 /std:c++17
cl.exe /D DEBUG src/core/utils.cpp /Fi utils.o -c /bigobj /W4 /O2 /std:c++17
cl.exe /D DEBUG src/core/shell.cpp /Fi shell.o -c /bigobj /W4 /O2 /std:c++17
cl.exe /D DEBUG src/chat/chatbox.cpp /Fi chatbox.o -c /bigobj /W4 /O2 /std:c++17
cl.exe ./utils.o ./shell.o ./chatbox.o ./src/core/cmd/*.cpp.o -o "output_chatbox" /bigobj /W4 /O2 /std:c++17


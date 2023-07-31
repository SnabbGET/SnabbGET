#! /bin/bash

g++ "include/exprtk/exprtk.hpp" -o "include/exprtk/exprtk.hpp.gch" -c -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough
for file in src/core/cmds; do
    g++ -D DEBUG $file -o $file.o -c -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough
done
g++ -D DEBUG src/core/utils.cpp -o utils.o -c -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough
g++ -D DEBUG src/core/shell.cpp -o shell.o -c -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough
g++ -D DEBUG src/chat/chatbox.cpp -o chatbox.o -c -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough
g++ ./utils.o ./shell.o ./chatbox.o ./src/core/cmd/*.cpp.o -o "output_chatbox" -Wa,-mbig-obj -Wall -Wextra -O3 -g3 -std=c++1z -fuse-ld=lld -Wno-implicit-fallthrough

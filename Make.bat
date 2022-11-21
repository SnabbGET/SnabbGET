g++ src/core/gen/includes_files.cpp -o "includes"
./includes.exe
g++ -Wall -Wextra -D DEBUG -g3 src/*.cpp src/core/utils.cpp -o "output"
./output.exe

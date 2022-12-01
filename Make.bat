g++ src/core/gen/includes_files.cpp -o "includes" -std=c++1z
./includes.exe
g++ -Wall -Wextra -D DEBUG -O3 -g3 src/*.cpp src/core/utils.cpp -o \
"output" -std=c++1z
./output.exe

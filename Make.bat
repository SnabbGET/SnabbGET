g++ -Wall -Wextra -D DEBUG -O3 -g3 src/*.cpp src/core/utils.cpp -o "output" -std=c++1z -L./libs/readline-8.2 -lreadline -lhistory -ltinfo
./output.exe

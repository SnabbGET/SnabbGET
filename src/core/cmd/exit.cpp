// Exit command

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <unistd.h>
#include <algorithm>

//#include "../shell.hpp"

std::string SnabbGET::CMDS::_exit_(std::string[], int, std::string)
{
	return "Bye!\n"; // Auto exit! (see in main.cpp)
}
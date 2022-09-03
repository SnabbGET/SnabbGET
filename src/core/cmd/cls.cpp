// Clear command

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

std::string SnabbGET::CMDS::_cls_(std::string[], int, std::string)
{
	return "\033[2J\033[H";
}
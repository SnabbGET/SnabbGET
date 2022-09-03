// Say command

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

std::string SnabbGET::CMDS::_say_(std::string[], int, std::string input_user)
{
	std::string msg = input_user.substr(4).c_str();
	msg += "\r\n";
	return msg;
}
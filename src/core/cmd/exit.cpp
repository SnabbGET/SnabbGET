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
/**
 * @brief Exit command
 * 
 * @param cmd [NOT USED]
 * @param cmdLen [NOT USED]
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_exit_(std::string[], int, std::string)
{
	#ifdef __linux__
		tcsetattr(0, TCSANOW, &old);
	#endif
	return "Bye!\n"; // Auto exit! (see in main.cpp)
}

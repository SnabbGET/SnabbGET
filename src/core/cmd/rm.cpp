// Rm command

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
#include <cstdio>
#include <cstring>
#include <cerrno>

//#include "../shell.hpp"

/**
 * @brief Rm command
 * 
 * @param cmd The user command in array
 * @param cmdLen The commands' array lenght
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_rm_(std::string cmd[], int cmdLen, std::string)
{
	if (cmdLen < 1)
		return "Error: you must give the file";
	
	std::remove(cmd[1].c_str());

    if (std::ifstream(cmd[1])) return "Error deleting file";
	return "Remove succeful!";
}

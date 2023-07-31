// Rm command

#include "../shell.hpp"

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
std::string SnabbGET::CMDS::_rm_(std::string cmd[], int &cmdLen, std::string&)
{
	if (cmdLen < 2)
	{
		THROW_ERR_MSG(err::BAD_INPUT, (char*)"You must give the file;");
		return "Failed";
	}
	
	std::remove(cmd[1].c_str());

    if (std::ifstream(cmd[1]))
	{
		THROW_ERR(err::ERR_DELETE_FILE);
		return "Failed";
	}
	else return "Remove succeful!";
}

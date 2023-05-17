// Mv command

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
 * @brief Mv command
 * 
 * @param cmd The user command in array
 * @param cmdLen The commands' array lenght
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_mv_(std::string cmd[], int cmdLen, std::string)
{
	if (cmdLen < 3)
	{
		THROW_ERR_MSG(err::BAD_INPUT,
			(char*)"you must give the source file and the destination dir");
		return "Failed";
	}
	
	std::string dst = cmd[1];
	
	if (cmd[2].find_last_of('/') == cmd[2].length() - 1)
		cmd[2] += cmd[1].erase(
				0, // start
				cmd[1].find_last_of('/') // pos of last /
					== std::string::npos ? // if not found ?
					0: // 0 chars will be erased
					cmd[1].find_last_of('/') + 1
			);
	#ifdef DEBUG
		std::cout << dst << "\r\n" << cmd[2] << "\r\n";
	#endif

	if (std::rename(dst.c_str(), cmd[2].c_str()) < 0)
	{
		return (std::string)strerror(errno);
	}

	return "Move succeful!";
}

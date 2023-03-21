// Cp command

#include "../shell.hpp"

// Yes, I know, the name of this file... ;)

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
 * @brief Cp command
 * 
 * @param cmd The user command in array
 * @param cmdLen The commands' array lenght
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_cp_(std::string cmd[], int cmdLen, std::string)
{
	if (cmdLen < 3)
	{
		THROW_ERR_MSG(err::BAD_INPUT,
			(char*)"You must give the source file and the destination file;");
		return "Failed";
	}

	std::ifstream src(cmd[1], std::ios::binary);
	std::ofstream dst(cmd[2], std::ios::binary);

	#ifdef DEBUG
		std::cout << cmd[1] << "\r\n" << cmd[2] << "\r\n";
	#endif

	if (!src.is_open() || !dst.is_open())
	{
		THROW_ERR(err::ERR_OPEN_FILE);
		return "Can't copy this file";
	}

	dst << src.rdbuf();

	return "Copy succeful!";
}

// Exe command

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
 * @brief Execute command [DELETED]
 * 
 * @param cmd [NOT USED]
 * @param cmdLen [NOT USED]
 * @param input_user The user input
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_exe_(std::string[], int, std::string input_user)
{
	/*
	__snabbget.__rawmode.pause();
	std::string msg = "cd ";
	#ifdef _WIN32
		if (__snabbget.currentDir.substr(0, 1) == "~")
		{
			msg += "&& cd ";
			msg += __snabbget.currentDir.substr(2);
		}
	#else
		msg += __snabbget.currentDir;
	#endif
	msg += " && ";
	msg += input_user.substr(4);
	system(msg.c_str());
	__snabbget.__rawmode.resume();
	// DEBUG: Success command execution message

	#ifdef DEBUG
		return "\r\n\033[92mCommand executed!\033[0m\r\n";
	#else
		if (cmd[1] == "cd")
			return "WARNING! You had enter a 'cd' command. THE DIRECTORY IS NOT SAVED! Use the SnabbGET command.\r\n";
		else
			return "";
	#endif*/return "error";
}


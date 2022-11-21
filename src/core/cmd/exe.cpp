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
#include <functional>

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
	try
	{
		//std::cout << "ok\r\n";
		//SnabbGET::Raw_mode::pause();
		//std::cout << "ok\r\n";
		std::string msg = "cd ", msg2;
		//std::cout << "ok\r\n";
		#ifdef _WIN32
			if (SnabbGET::currentDir.substr(0, 1) == "~")
			{
				msg += "%%USERPROFILE%% && cd ";
				msg += SnabbGET::currentDir.substr(2);
			}
		#else
			msg += SnabbGET::currentDir;
		#endif
		//std::cout << "ok\r\n";
		msg += " && ";
		//std::cout << "ok\r\n";
		msg += input_user.substr(4);
		//std::cout << "ok\r\n";
		msg2 = exec(msg.c_str());
		//std::cout << "ok\r\n";
		//SnabbGET::Raw_mode::resume();
		//std::cout << "ok\r\n";

		// DEBUG: Success command execution message
		#ifdef DEBUG
			return replaceAll(msg2, "\n", "\r\n") +
				"\r\n\033[92mCommand executed!\033[0m";
		#else
			/*if (SnabbGET::cmd[1] == "cd")
				return "WARNING! You had enter a 'cd' command. THE DIRECTORY \
IS NOT SAVED! Use the SnabbGET command.\r\n";
			else*/
				return msg2;
		#endif
	}
	catch (std::bad_function_call& e)
	{
		return "ERROR in EXE command";
	}
}

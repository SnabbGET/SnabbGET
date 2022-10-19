// Cd command

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

#ifndef _CD_

	#define _CD_

	// #include "../shell.hpp" // NO
	/**
	 * @brief CD command [DELETED]
	 * 
	 * @param cmd The commands in array
	 * @param cmdLen The commands' array lenght
	 * @param input_user [NOT USED]
	 * @return [std::string] Command result
	 */
	std::string SnabbGET::CMDS::_cd_(std::string cmd[], int cmdLen, std::string)
	{
		/*std::string msg = "cd ";
		msg += cmd[1];
		if (! system(msg.c_str()))
		{
			if (cmdLen > 1)
				__snabbget.currentDir = cmd[1];
			else
				__snabbget.currentDir = "~";

			#ifdef _WIN32
				setcwd(currentDir.c_str());
			#elif __linux__
				setenv("PWD", __snabbget.currentDir.c_str(), 1);
			#endif
			__snabbget.set_current_dir();
			return __snabbget.currentDir;
		}
		else*/
			return "\rError";
	}

#endif
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
	 * @brief CD command
	 * 
	 * @param cmd The command in array
	 * @param cmdLen The commands' array lenght
	 * @param input_user [NOT USED]
	 * @return [std::string] Command result
	 */
	std::string SnabbGET::CMDS::_cd_(std::string cmd[], int cmdLen, std::string)
	{
		std::string msg = "cd ";
		msg += __snabbget.currentDir;
		msg += " && cd ";
		msg += cmd[1];
		#ifdef DEBUG
			std::cout << "CMD = " << msg << "\r\n";
		#endif
		if (! system(msg.c_str()))
		{
			/*if (cmdLen > 1)
				__snabbget.currentDir = cmd[1];
			else
				__snabbget.currentDir = "~";*/

			#ifdef _WIN32

				setcwd(currentDir.c_str());
			#elif __linux__
				if (cmdLen > 1)
				{
					msg = "cd ";
					msg += __snabbget.currentDir;
					msg += " && cd ";
					msg += cmd[1];
					msg += " && pwd";
					#ifdef DEBUG
						std::cout << "CMD = " << msg << "\r\n";
					#endif
					__snabbget.currentDir = 
						((std::string)exec(msg.c_str())) // the result
							.find_last_of('\n') != std::string::npos ?  // \n is found?
						((std::string)exec(msg.c_str())) //the result
							.erase( // delete
								((std::string)exec(msg.c_str())).length() - 1, // length of the result
								1 // number of char
							) :
						((std::string)exec(msg.c_str())); // the result
				}
				else
					__snabbget.currentDir = "~";
				setenv("PWD", __snabbget.currentDir.c_str(), 1);
			#endif
			__snabbget.set_current_dir();
			return __snabbget.currentDir;
		}
		else
			return "\rError";
	}

#endif

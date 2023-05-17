// Cd command

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
#include <filesystem>

#ifndef _CD_

	#define _CD_

	// #include "../shell.hpp" // NO // SI
	/**
	 * @brief CD command
	 * 
	 * @param cmd The command in array
	 * @param cmdLen The commands' array lenght
	 * @param input_user [NOT USED]
	 * @return [std::string] Command result
	 */

	extern std::string SnabbGET::currentDir;

	std::string SnabbGET::CMDS::_cd_(std::string cmd[], int cmdLen,std::string)
	{
		#if __cplusplus >= 201703L
			if (contain(cmd, cmdLen, "--pwd") || contain(cmd, cmdLen, "-p"))
			{
				return SnabbGET::currentDir;
			}
			else
			{
				std::string msg = "cd ";
				msg += SnabbGET::currentDir;
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
						std::filesystem::current_path(
							SnabbGET::currentDir.c_str());
					#elif __linux__
						if (cmdLen > 1)
						{
							msg = "cd ";
							msg += SnabbGET::currentDir;
							msg += " && cd ";
							msg += cmd[1];
							msg += " && pwd";
							#ifdef DEBUG
								std::cout << "CMD = " << msg << "\r\n";
							#endif
							SnabbGET::currentDir = 
								((std::string)exec(msg.c_str())) // the result
									.find_last_of('\n') != std::string::npos ? 
									// \n is found?
								((std::string)exec(msg.c_str())) //the result
									.erase( // delete
										((std::string)exec(msg.c_str())).length() - 1,
										// length of the result
										1 // number of char
									) :
								((std::string)exec(msg.c_str())); // the result
						}
						else
							SnabbGET::currentDir = "~";
						setenv("PWD", SnabbGET::currentDir.c_str(), 1);
					#endif
					SnabbGET::set_current_dir();
					return SnabbGET::currentDir;
				}
				else
				{
					THROW_ERR_MSG(err::BAD_INPUT, (char*)"Can't CD here;");
					return "\rFailed";
				}
			}
		#else
			THROW_ERR(err::BAD_VERSION);
			return "";
		#endif
	}

#endif

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

	std::string SnabbGET::CMDS::_cd_(std::string cmd[], int &cmdLen, std::string&)
	{
		#if __cplusplus >= 201703L
			if (contain(cmd, cmdLen, "--pwd") || contain(cmd, cmdLen, "-p"))
			{
				return SnabbGET::currentDir;
			}
			else
			{
				std::filesystem::path path{cmd[1]};

				if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
				{
					#ifdef __linux__
					if (cmdLen > 1)
					{
					#endif
						std::filesystem::current_path(path);
						SnabbGET::currentDir = path.string();
							
						SnabbGET::currentDir = 
							currentDir.find_last_of('\n') != std::string::npos ? 
								// \n is found?
							currentDir.erase( // delete
									currentDir.length() - 1,
									// length of the result
									1 // number of char
								) :	currentDir; // the result
					#ifdef __linux__
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

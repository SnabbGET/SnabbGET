// Mk command

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
 * @brief Mk command
 * 
 * @param cmd The user command in array
 * @param cmdLen The commands' array lenght
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_mk_(std::string cmd[], int cmdLen, std::string)
{
	if (cmdLen < 2)
		return "Error: you must give the new file";
	
	std::ofstream outfile(cmd[1].c_str());
	outfile.close();
	outfile.open(cmd[1].c_str(), std::ios_base::app);

	// Check the file
	if (!outfile.is_open())
	{
		#ifdef DEBUG
			std::cout << "Error opening file!" << std::endl;
		#endif

		// Try to create the file
		outfile.open(cmd[1].c_str(), std::ios_base::out);
		if (!outfile.is_open())
		{
			#ifdef DEBUG
				std::cout << "Error creating file!" << std::endl;
			#endif

			system(("cd " + SnabbGET::currentDir + " && echo \"\" > " + cmd[1]).c_str());

			// Try to open the file again
			outfile.open(cmd[1].c_str(), std::ios_base::app);
			if (!outfile.is_open())
			{
				#ifdef DEBUG
					std::cout << "Error opening file!" << std::endl;
				#endif
				
				return "Error: can't make this file";
			}

		}
	}
	outfile.close();
	
	return "Make succeful!";
}

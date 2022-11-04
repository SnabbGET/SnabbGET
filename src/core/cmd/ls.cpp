// Ls command

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
#include <dirent.h>

//#include "../shell.hpp"

/**
 * @brief Ls command
 * 
 * @param cmd [NOT USED]
 * @param cmdLen [NOT USED]
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_ls_(std::string[], int, std::string)
{
	std::string msg = "";
	DIR *dir;
	struct dirent *diread;
	std::vector<char *> files;

	std::string currDir = SnabbGET::currentDir;
	if (currDir.find("~") == 0)
	{
		std::string r = ((std::string)exec("echo ~")) // the result
							.find_last_of('\n') != std::string::npos ?  // \n is found?
						((std::string)exec("echo ~")) //the result
							.erase( // delete
								((std::string)exec("echo ~")).length() - 1, // length of the result
								1 // number of char
							) :
						((std::string)exec("echo ~")); // the result
		currDir.erase(0, 1);
		currDir = r + currDir;
	}

	#ifdef DEBUG
		std::cout << currDir << "\r\n";
	#endif

	if ((dir = opendir(currDir.c_str())) != nullptr)
	{
		while ((diread = readdir(dir)) != nullptr)
		{
			if (((std::string)diread->d_name).rfind(".", 0) == std::string::npos)
				files.push_back(diread->d_name);
		}
		closedir(dir);
	}
	else
	{
		perror("opendir");
		return "\rError: can't list this dir";
	}

	for (auto file : files)
	{
		msg += file;
		msg += "\r\n";
	}
	return msg;
}

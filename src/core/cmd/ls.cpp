// Ls command

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <filesystem>

//#include "../shell.hpp"


std::string h(std::uintmax_t size)
{
	int i{};
	double mantissa = size;
	for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }
	short a = std::round(std::ceil(mantissa * 10.) / 10.);
	//mantissa += "BKMGTPE"[i];
	return std::to_string(a) + "oKMGTPE"[i] + (i > 1 ? 'o':' ');
}

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
	std::vector<char *> files;

	std::string currDir = SnabbGET::currentDir;
	if (currDir.find("~") == 0)
	{
		#ifdef __WIN32
			std::string = "%%USERPROFILE%%";
		#else
			std::string r = ((std::string)exec("echo ~")) // the result
								.find_last_of('\n') != std::string::npos ?
								// \n is found?
							((std::string)exec("echo ~")) //the result
								.erase( // delete
									((std::string)exec("echo ~")).length() - 1,
									// length of the result
									1 // number of char
								) :
							((std::string)exec("echo ~")); // the result
		#endif
		currDir.erase(0, 1);
		currDir = r + currDir;
	}

	#ifdef DEBUG
		std::cout << currDir << "\r\n";
	#endif

	/*if ((dir = opendir(currDir.c_str())) != nullptr)
	{
		while ((diread = readdir(dir)) != nullptr)
		{
			if (((std::string)diread->d_name).rfind(".", 0)==std::string::npos)
				files.push_back(diread->d_name);
		}
		closedir(dir);
	}
	else
	{
		perror("opendir");
		return "\rError: can't list this dir";
	}*/

	std::error_code ec;
	for (const auto &entry:std::filesystem::directory_iterator(currDir))
	{
		std::filesystem::file_size(entry, ec);
		if (!ec)
			msg += std::string("\t\t\t\t\t") +h(entry.file_size())+"\r";
		msg += (entry.is_directory() ? "\033[38;5;75m":
					(entry.is_regular_file() ? "\033[0m":
					(entry.is_other() ? "\033[38;5;118m":
					(entry.is_socket() ? "\033[38;5;193m":
					(entry.is_block_file() ? "\033[38;5;220m":
					(entry.is_character_file() ? "\033[38;5;161m":
					(entry.is_fifo() ? "\033[38;5;99":"\033[38;5;203m"))
					))))) + 
			std::string(replaceAll(
				replaceAll(
					replaceAll(entry.path(), currDir, ""),
					"/", ""
				), "\\", ""
			)) + std::string("\033[0m\r\n");
	}
	return msg;
}

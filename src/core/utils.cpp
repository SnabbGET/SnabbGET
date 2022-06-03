// Main file

/**
 * @file src/code/utils.cpp
 * @brief Utils.
 * @author LAPCoder
 * @version 0.0.0
 * 
 * MIT License
 */
 
#include <chrono>
#include <iostream>
#include <string>

#include "utils.hpp"

std::string getdate()
{
	// get formatted date
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::string date = std::ctime(&now_c);
	date.erase(date.end() - 1);
	return date;
}

std::string gettime()
{
	// get formatted time
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::string time = std::ctime(&now_c);
	time.erase(time.begin(), time.begin() + 13);
	return time;
}

std::string help_params(std::string cmd)
{
	if (cmd == "help")
	{
		return "\
Description: \n\
\033[32mPrint documentation in the terminal.\033[0m\n\
\n\
		| --web => open documentation of commands in web browser\n";
	} else {
		return "No documentation found for the command " + cmd + ".\n";
	}
}

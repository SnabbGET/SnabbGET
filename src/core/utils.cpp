// Main file

/**
 * @file src/code/utils.cpp
 * @brief Utils.
 * @author LAPCoder
 * @version 0.0.1
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
		return "\
Description: \r\n\
\033[32mPrint documentation in the terminal.\033[0m\r\n\
\r\n\
	--web => open documentation of commands in web browser\n";
	else 
		return "No documentation found for the command '" + cmd + "'.\r\n";
}

bool contain(std::string *lst, unsigned int lstLen, std::string tfind)
{
	for (unsigned int i = 0; i < lstLen; i++)
		if (lst[i] == tfind) return true;
	return false;
}

std::string hexToDec(std::string num)
{
	unsigned int hex;   
	std::stringstream num1 = (std::stringstream)num;
	
	num1 << std::hex << num;
	num1 >> hex;

	#ifdef DEBUG
		std::cout << num << " hexToDec " << hex << "\r\n";
	#endif

	return std::to_string(hex);
}

std::string htmlToRgbEsc(std::string htmlColor, int isForeground)
{
	std::string red = htmlColor.substr(1, 2);
	std::string green = htmlColor.substr(3, 2);
	std::string blue = htmlColor.substr(5, 2);
	
	
	return "\033[" + (std::string)(isForeground ? "3":"4") + "8;2;" + hexToDec(red) + ";" + hexToDec(green) + ";" + hexToDec(blue) + "m";
}

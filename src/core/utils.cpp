// Main file

/**
 * @file src/code/utils.cpp
 * @brief Utils.
 * @author LAPCoder
 * @version 0.1.0
 * 
 * MIT License
 */
 
#include <chrono>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <vector>
#include <iterator>
#include <sstream>

#include "utils.hpp"

std::string getdate()
{
	// get formatted date
	std::chrono::system_clock::time_point now =
		std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::string date = std::ctime(&now_c);
	date.erase(date.end() - 1);
	return date;
}

std::string gettime()
{
	// get formatted time
	std::chrono::system_clock::time_point now =
		std::chrono::system_clock::now();
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
	else if (cmd == "mk")
		return "\
Description: \r\n\
\033[32mCreate a file or a directory.\033[0m\r\n\
\r\n\
	-d,\r\n\
	--dir => create a directory instead of a file.\n";
	else if (cmd == "cd")
		return "\
Description: \r\n\
\033[32mChange directory or print the current dir.\033[0m\r\n\
\r\n\
	-p,\r\n\
	--pwd => print current dir. YOU CAN'T CHANGE OF DIR WITH THIS \
OPTION!\n";
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
		//std::cout << num << " hexToDec " << hex << "\r\n";
	#endif

	return std::to_string(hex);
}

std::string htmlToRgbEsc(std::string htmlColor, int isForeground)
{
	std::string red = htmlColor.substr(1, 2);
	std::string green = htmlColor.substr(3, 2);
	std::string blue = htmlColor.substr(5, 2);
	
	
	return "\033[" + (std::string)(isForeground ? "3":"4") +
		"8;2;" + hexToDec(red) + ";" + hexToDec(green) + ";" +
		hexToDec(blue) + "m";
}

std::string exec(const char* cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

std::string concatArr(std::string arr[], int N)
{
	std::string tmp = "";
	for (int i = 0; i < N - 1; i++)
	{
		tmp += arr[i];
		tmp += " ";
	}
	tmp.erase(tmp.length() - 1);

	return tmp;
}

std::string replaceAll(std::string str, const std::string &from,
						const std::string &to)
{
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); 
		// Handles case where 'to' is a substring of 'from'
	}
	return str;
}

std::string join(std::vector<std::string> const &strings, const char *delim)
{
    std::stringstream ss;
    std::copy(strings.begin(), strings.end(),
        std::ostream_iterator<std::string>(ss, delim));
    return ss.str();
}

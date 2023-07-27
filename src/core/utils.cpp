// Main file
#ifndef __SGET_UTILS
#define __SGET_UTILS
/**
 * @file src/code/utils.cpp
 * @brief Utils.
 * @author LAPCoder
 * @version 0.2.0
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
#ifdef __WIN32
	#include <windows.h>
#else
	#include <termios.h>
	#include <unistd.h>
#endif

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
	std::time_t t = std::time(0);
	std::tm *now = std::localtime(&t);
	return std::string(std::to_string(now->tm_hour) + ":" + 
					   std::to_string(now->tm_min) + ":" + 
					   std::to_string(now->tm_sec));
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

std::string exec(const char *cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		std::cout << buffer.data();
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

std::vector<std::string> split(const std::string &s, const char &token)
{
	std::vector<std::string>result;
	std::string str = s;
	while (str.size())
	{
		// F*ck the unsigned
		int index = str.find(token);
		if (index != (long long)std::string::npos)
		{
			result.push_back(str.substr(0,index));
			str = str.substr(index+1);
			if (str.size() == 0)
				result.push_back(str);
		}
		else
		{
			result.push_back(str);
			break;
		}
	}
	return result;
}

int get_pos(int *y, int *x)
{
	#ifdef __WIN32
		CONSOLE_SCREEN_BUFFER_INFO cbsi;
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
		{
			*x = cbsi.dwCursorPosition.X;
			*y = cbsi.dwCursorPosition.Y;
		}
		else
		{
			// The function failed. Call GetLastError() for details.
			return 1;
		}
	#else
		char buf[30] = {0};
		int ret, i, pow;
		char ch;
		*y = 0; *x = 0;

		struct termios term, restore;

		tcgetattr(0, &term);
		tcgetattr(0, &restore);
		term.c_lflag &= ~(ICANON|ECHO);
		tcsetattr(0, TCSANOW, &term);

		write(1, "\033[6n", 4);

		for (i = 0, ch = 0; ch != 'R'; i++)
		{
			ret = read(0, &ch, 1);
			if (!ret) {
				tcsetattr(0, TCSANOW, &restore);
				fprintf(stderr, "get_pos: Error reading response!\r\n");
				return 1;
			}
			buf[i] = ch;
			//printf("buf[%d]: \t%c \t%d\r\n", i, ch, ch);
		}

		if (i < 2)
		{
			tcsetattr(0, TCSANOW, &restore);
			printf("i < 2\r\n");
			return 1;
		}

		for (i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
			*x = *x + ( buf[i] - '0' ) * pow;

		for (i--, pow = 1; buf[i] != '['; i--, pow *= 10)
			*y = *y + ( buf[i] - '0' ) * pow;

		tcsetattr(0, TCSANOW, &restore);
	#endif
	return 0;
}

#endif // __SGET_UTILS

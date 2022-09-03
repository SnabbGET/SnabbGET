// Main file

/**
 * @file src/main.cpp
 * @brief Main file of the project.
 * @author LAPCoder
 * @version 0.0.1
 * 
 * MIT License
 */

/* DEFINES */
//See shell.hpp
//#define VERSION "0.0.1"

/* INCLUDES */

#include "core/shell.hpp"
//#include "interface/gui.cpp"

#ifndef std_def
	#include <iostream>
	#include <cstdio>
	#include <string>
	#include <chrono>
	#include <cstdio>
	#define std_def
	#define print(x, ...) std::cout << x // For a friend :D
#endif

/* INSTANCES */

// Main
// Graphics
// GUI gui;

/* Start */

std::string input_user;
std::string input_user_tmp;

int main(int agrc, char **argv)
{
	SnabbGET sget;
	SnabbGET::Raw_mode rw(0);
	std::cout << sget.init() ;//<< "\0337\n\0338";
	while (true)
	{
		//getline(std::cin, input_user);
		// Raw mode: BIG SH*T
		int c = '\0';
		input_user = "";
		int right_count = 0;

		// Not really char count, but the number of chars left to read
		int chars_count = 0;

		// Use the Raw mode to read the input from the user
		// and hide escape sequences (e.g. ^[[A).
		while (1)
		{
			input_user_tmp = "";
			read(0, &c, 1);
			if (c == '\n') break;
			if (((32  <= c) && 
				 (126 >= c)) || 
				((161 <= c) &&
				 (255 >= c)) ||
				c == rw.TAB)
			{
				input_user += (char)c;
				input_user_tmp = (char)c;
				chars_count++;
			}
			if (c == rw.BACKSPACE)
			{
				if (input_user.length() > 0)
				{
					input_user.erase(input_user.length() - 1);
					chars_count--;
				}
				input_user_tmp = "\033[D \033[D";
			}
			if (c == rw.DEL_KEY)
			{
				if (input_user.length() > 0 && right_count > 0)
				{
					input_user.erase(input_user.length() - 1);
					right_count--;
				}
				input_user_tmp = "\033[D \033[D";
			}
			if ((int)c == rw.ESC) // ESC like \[ \033 \x1b
			{
				read(0, &c, 1);
				if (c == '[')
				{
					read(0, &c, 1);
					//if (c == 'A') input_user += "UP";
					//if (c == 'B') input_user += "DOWN";
					if (c == 'C' && right_count > 0)
					{
						input_user_tmp = "\033[C";
						input_user += "\033[C";
						right_count--;
						chars_count++;
					}
					if (c == 'D' && chars_count > 0)
					{
						input_user_tmp = "\033[D";
						input_user += "\033[D";
						right_count++;
						chars_count--;
					}
				}
			}
			std::cout << input_user_tmp << /*"(" << (int)c << ")" << */"\033[1A\n";
		}

		std::cout << "\r\n" << sget.read_input(input_user);

		if (input_user == "exit") 
		{
			//sget.~SnabbGET();
			return EXIT_SUCCESS;
			exit(EXIT_SUCCESS);
		}
		else std::cout << "\r\n" << sget.new_line();
	}
	return 0;
}

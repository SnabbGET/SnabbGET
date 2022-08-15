// Main file

/**
 * @file src/main.cpp
 * @brief Main file of the project.
 * @author LAPCoder
 * @version 0.0.0
 * 
 * MIT License
 */

/* DEFINES */

#define VERSION "0.0.0"

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

int main()
{
	SnabbGET sget;
	SnabbGET::Raw_mode rw(0);
	std::cout << sget.init() ;//<< "\0337\n\0338";
	while (true)
	{
		//getline(std::cin, input_user);
		// Raw mode: BIG SH*T
		char c = '\0';
		input_user = "";
		// Use the Raw mode to read the input from the user
		// and hide escape sequences (e.g. ^[[A).
		while (1)
		{
			input_user_tmp = "";
			read(0, &c, 1);
			if (c == '\n') break;
			if (((32  <= (int)c) && 
				(126 >= (int)c)) || 
				((161 <= (int)c) &&
				(255 >= (int)c)))
				{
					input_user += c;
					input_user_tmp = c;
				}
			if ((int)c == rw.ESC) // ESC like \[ \033 \x1b
			{
				read(0, &c, 1);
				if (c == '[')
				{
					read(0, &c, 1);
					/*if (c == 'A') input_user += "UP";
					if (c == 'B') input_user += "DOWN";
					if (c == 'C') input_user += "RIGHT";
					if (c == 'D') input_user += "LEFT";*/
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

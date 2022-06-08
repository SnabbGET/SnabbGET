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
	#define std_def
	#define print(x, ...) std::cout << x << std::endl
#endif

/* INSTANCES */

// Main
// Graphics
// GUI gui;

/* Start */

std::string input_user;

int main()
{
	SnabbGET sget;
	std::cout << sget.init();
	/*std::cout << sget.new_line();*///Decomment for raw mode
	while (true)
	{
		getline(std::cin, input_user);
		/* // Raw mode!
		char c = 0;
		std::string input_user = "";
		while ((int)c != 10)
		{
			read(0, &c, 1);
			if (((32  <= (int)c) && 
				 (126 <= (int)c)) || 
				((161 <= (int)c) &&
				 (255 >= (int)c))) input_user += c;
		}*/
		std::cout << sget.read_input(input_user);

		if (input_user == "exit") 
		{
			sget.~SnabbGET();
			exit(EXIT_SUCCESS);
		}
		else std::cout << sget.new_line();
	}
	return 0;
}

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
// #include "interface/gui.cpp"

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
	while (true)
	{
		getline(std::cin, input_user);
		std::cout << sget.read_input(input_user);

		if (input_user == "exit") exit(EXIT_SUCCESS);
		else std::cout << sget.new_line();
	}
}
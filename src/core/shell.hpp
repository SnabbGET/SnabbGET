#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <unistd.h>
#include <termios.h>
#include <cstdio>

#include "utils.hpp"

#define VERSION "0.0.0"

#define ZERO_ANY(T, a, n) do{\
	T *a_ = (a);\
	size_t n_ = (n);\
	for (; n_ > 0; --n_, ++a_)\
		*a_ = (T) { 0 };\
} while (0)


/* Initialize new terminal i/o settings */
static struct termios old, new1;


// Class with the shell.
class SnabbGET
{
	public:
		// Constructor.
		SnabbGET();
		// Destructor.
		~SnabbGET();
		// Initialize the shell.
		std::string init();

		// Read the input from the user.
		std::string read_input(std::string input_user_t);
		// Print a new line.
		std::string new_line();

	private:
		// Last user input.
		std::string input_user;
		// Time when the shell was started.
		std::time_t dateOpen;
		// File with the history.
		std::ofstream historyFile;

		// User name and computer name.
		std::string userName = "User";
		std::string computerName = "Computer";
		std::string currentDir = "/";

		// Get user's name
		void set_user_name();
		// Get user PC name
		void set_machine_name();
		// Get current directory
		void set_current_dir();

		// Put user's command in array.
		void get_command(std::string input_user_t);
		std::string cmd[MAX_INPUT];
		unsigned int cmdLen = 0;

		std::string TOGGLE_DEBUG();

		class Raw_mode
		{
			public:
				Raw_mode(int echo);
				~Raw_mode();
		};
};

#ifdef FILEENUMERR
	#include "shell.cpp"
#endif

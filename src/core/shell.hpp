#pragma once

/**
 * @file src/core/shell.hpp
 * @brief Header of the main part.
 * @author LAPCoder
 * @version 0.0.1
 * 
 * MIT License
 */

// Class with the shell.

#ifndef SNABBGET_CORE

	#include <iostream>
	#include <string>
	#include <chrono>
	#include <ctime>
	#include <fstream>
	#include <cstdlib>
	#include <climits>
	#include <unistd.h>
	#include <termios.h>
	#include <functional>
	#include <vector>

	#include "utils.hpp"

	#define VERSION "0.0.1"

	#define ZERO_ANY(T, a, n) do{\
		T *a_ = (a);\
		size_t n_ = (n);\
		for (; n_ > 0; --n_, ++a_)\
			*a_ = (T) { 0 };\
	} while (0)

	#define SNABBGET_CORE

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

			// Active the raw mode to get a best terminal experience.
			class Raw_mode
			{
				public:
					Raw_mode();
					Raw_mode(int echo);
					~Raw_mode();


					static void pause();
					static void resume();

					enum KEY_ACTIO
					{
						KEY_NULL = 0,		/* NULL */
						CTRL_C = 3,			/* Ctrl-c */
						CTRL_D = 4,			/* Ctrl-d */
						CTRL_F = 6,			/* Ctrl-f */
						CTRL_H = 8,			/* Ctrl-h */
						TAB = 9,			/* Tab */
						CTRL_L = 12,		/* Ctrl+l */
						ENTER = 13,			/* Enter */
						CTRL_Q = 17,		/* Ctrl-q */
						CTRL_S = 19,		/* Ctrl-s */
						CTRL_U = 21,		/* Ctrl-u */
						ESC = 27,			/* Escape */
						BACKSPACE =  127,	/* Backspace */
						ARROW_LEFT = 1000,
						ARROW_RIGHT,
						ARROW_UP,
						ARROW_DOWN,
						DEL_KEY,
						HOME_KEY,
						END_KEY,
						PAGE_UP,
						PAGE_DOWN
					};
			};

		protected:
			//Raw_mode __rawmode;

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

			// All commands
			class CMDS
			{
				public:
					CMDS();
					~CMDS();

					#ifndef CMDS_DEF
						#define CMDS_DEF
						
						#define EXIT 0
						#define HELP 1
						#define CLS  2
						#define SAY  3
						#define CD   4
						#define EXE  5
					#endif

					static std::string _exit_(std::string[], int, std::string);
					static std::string _help_(std::string[], int, std::string);
					static std::string _cls_ (std::string[], int, std::string);
					static std::string _say_ (std::string[], int, std::string);
					static std::string _cd_  (std::string[], int, std::string);
					static std::string _exe_ (std::string[], int, std::string);

					

					std::vector<std::function<std::string(std::string[], int, std::string)>> cmdLst;
			} run;

			std::string runCmd(int id, std::string[], int, std::string);

		private:
			std::string TOGGLE_DEBUG();
	} __snabbget;


	// WARNING!!!!! THOSE LINES MUST STAY LIKE THAT!!!
	//                          ====
	#include "shell.cpp"
	#include "./includesAll.hpp"

#endif // SNABBGET_CORE


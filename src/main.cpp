// Main file

/**
 * @file src/main.cpp
 * @brief Main file of the project.
 * @author LAPCoder
 * @version 0.1.0
 * 
 * MIT License
 */

/* DEFINES */
//See shell.hpp
//#define VERSION "0.1.0"

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

// WebAssembly
#ifdef __EMSCRIPTEN__ 
	#include <emscripten.h>
	bool one_line = true;
#else
	bool one_line = false;
#endif

#ifdef __cplusplus
	#define EXTERN extern "C"
#else
	#define EXTERN
#endif

#ifndef EMSCRIPTEN_KEEPALIVE
	#define EMSCRIPTEN_KEEPALIVE
#endif

#ifdef _FORJAVAGUI_

int main()
{	
	sget::SnabbGET();
	sget::rw::Raw_mode(0);
	sget::init();
	std::cout << sget::new_line();
	sget::read_input("exit");
	return EXIT_SUCCESS;
}

#else

EXTERN EMSCRIPTEN_KEEPALIVE void RunSnabbGETCommand(int argc, char **argv)
{
	sget::SnabbGET();
	sget::rw::Raw_mode(0);
	sget::init();
	std::string cmd;
	std::cin >> cmd;
	std::cout << sget::read_input(cmd) << "\r\n";
	std::string tmp[0];
	sget::CMDS::_exit_(tmp, 0, "");
}

// End Wasm

/* Start */

std::string input_user;
std::string input_user_tmp;

int main(int argc, char *argv[])
{
	sget::SnabbGET();
	sget::rw::Raw_mode(0);
	system(""); // I don't kwon why I must put that, but if I don't add that, escape codes don't work on Windows :(
	if (argc == 1 && !one_line)
	{
		//using namespace SnabbGET sget;
		//using SnabbGET::Raw_mode rw(0);
		std::cout << sget::init();//<< "\0337\n\0338";
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
					c == sget::rw::TAB)
				{
					input_user += (char)c;
					input_user_tmp = (char)c;
					chars_count++;
				}
				if (c == sget::rw::BACKSPACE)
				{
					if (input_user.length() > 0)
					{
						input_user.erase(input_user.length() - 1);
						chars_count--;
					}
					input_user_tmp = "\033[D \033[D";
				}
				if (c == sget::rw::DEL_KEY)
				{
					if (input_user.length() > 0 && right_count > 0)
					{
						input_user.erase(input_user.length() - 1);
						right_count--;
					}
					input_user_tmp = "\033[D \033[D";
				}
				if ((int)c == sget::rw::ESC) // ESC like \[ \033 \x1b
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
				#ifdef __linux__
					std::cout << input_user_tmp << /*"(" << (int)c << ")" << */"\033[1A\n";
				#endif
			}

			std::cout << "\r\n" << sget::read_input(input_user);

			if (input_user == "exit") 
			{
				return EXIT_SUCCESS;
				exit(EXIT_SUCCESS);
			}
			else std::cout << "\r\n" << sget::new_line();
		}
		return 0;
	}
	else if (argc > 1 && !one_line)
	{
		sget::SnabbGET(true);
		//sget::rw::Raw_mode(0);
		sget::init();
		std::string arr[MAX_INPUT];
		for(int b = 0; b < argc - 1 ; b++)
		{
			arr[b] = argv[b + 1];
		}
		//std::cout << concatArr(arr, argc) << std::endl;
		std::cout << sget::read_input(concatArr(arr, argc)) << "\r\n";
		sget::read_input("exit");
		//sget::rw::pause();
		return EXIT_SUCCESS;
	}
	else // one_line
	{
		/*SnabbGET sget(true);
		SnabbGET::Raw_mode rw(0);
		sget.init();
		std::string cmd;
		std::cin >> cmd;
		std::cout << sget.read_input(cmd) << "\r\n";
		return EXIT_SUCCESS;*/
	}
}

#endif

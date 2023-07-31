// Main file

/**
 * @file src/main.cpp
 * @brief Main file of the project.
 * @author LAPCoder
 * @version 0.2.0
 * 
 * MIT License
 */

/* DEFINES */
// See shell.hpp
//#define VERSION "0.2.0"

/* INCLUDES */

#include "core/shell.hpp"
//#include "interface/gui.cpp"
#ifndef READLINE_LIBRARY
	#define READLINE_LIBRARY
#endif
#ifndef std_def
	#include <iostream>
	#include <cstdio>
	#include <string>
	#include <chrono>
	#include <cstdio>
	#include <vector>
	#include <sstream>
	#define std_def
	#define print(x, ...) std::cout << x // For a friend :D

	#include "../include/readline/readline.h"
	#include "../include/readline/history.h"
#endif
#ifdef HAVE_LOCALE_H
	#include <locale.h>
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
	sget::init();
	std::cout << sget::new_line();
	sget::read_input("exit");
	return EXIT_SUCCESS;
}

#else 

//EXTERN EMSCRIPTEN_KEEPALIVE v

EXTERN EMSCRIPTEN_KEEPALIVE void RunSnabbGETCommand(
	/*int argc, char **argv*/)
{
	sget::SnabbGET();
	sget::init();
	std::string cmd;
	std::cin >> cmd;
	std::cout << sget::read_input(cmd) << "\r\n";
	std::string tmp[0];
	sget::CMDS::_exit_(tmp, 0, std::string(""));
}

// End Wasm

/* Start */

//extern sget::io::io.out

//std::string input_user;
//std::vector<char16_t> input;
//long pos;

int main(int argc, char *argv[])
{
	sget::SnabbGET();
	sget::rw::Raw_mode(0, false);
	sget::io::io.outFunct = &std::printf;
	sget::io::io.inFunct = &std::scanf;
	// To use: io << "foo"; io >> bar;
	
	#ifdef HAVE_SETLOCALE
		setlocale(LC_ALL, "");
	#endif

	system(""); // I don't kwon why I must put that, but if I don't add that,
				// escape codes don't work on Windows :(
	if (argc == 1 && !one_line)
	{
		sget::addToSCREEN(sget::init());
		// Printf is faster than std::cout and \n is faster than std::endl
		printf("%s", sget::FRAME().c_str());
		char *line;

		while (true)
		{
			line = readline(("\r\n" + sget::new_line()).c_str());
			try
			{
				if (!line) break;
				if (*line)
					add_history(line);
			}
			catch (std::logic_error &e)
			{}

			sget::addToSCREEN(sget::new_line());
			sget::SCREEN.back() += std::string(line);
			sget::addToSCREEN(sget::read_input(std::string(line)));
			printf("%s", (sget::FRAME()).c_str());

			if (strstr(line, "exit") != NULL) 
			{
				std::cout << "";
				return EXIT_SUCCESS;
				exit(EXIT_SUCCESS);
			}

			free(line);
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
}

#endif

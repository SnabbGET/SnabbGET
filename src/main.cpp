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

#include "./core/shell.hpp"
//#include "interface/gui.cpp"
#ifndef READLINE_LIBRARY
	#define READLINE_LIBRARY
#endif
#ifndef std_def
	#include <iostream>
	#include <cstdio>
	#include <string>
	#include <cstring>
	#include <chrono>
	#include <vector>
	#include <sstream>
	#define std_def
	#define print(x, ...) std::cout << x // For a friend :D

	#include "../include/isocline/isocline.h"
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
	int x = 0;
	std::string y("");
	sget::CMDS::_exit_(tmp, x, y);
}

// End Wasm

/* Start */

//extern sget::io::io.out

//std::string input_user;
//std::vector<char16_t> input;
//long pos;

// ISOCLINE FUNCS

static void word_completer(ic_completion_env_t* cenv, const char* word )
{
	for (auto a : sget::CMDS::allCmd)
		if (word[0] != 0 && ic_istarts_with(a[0], word))
			ic_add_completion_ex(cenv, a[0], a[0], a[1]);
}

static void completer(ic_completion_env_t* cenv, const char* input)
{
	ic_complete_filename(cenv, input, 0, ".;/usr/local;c:\\Program Files" , NULL);
	ic_complete_word(cenv, input, &word_completer, NULL);        
}

static void highlighter(ic_highlight_env_t* henv, const char* input, void* arg)
{
	(void)(arg);
	
	long len = (long)strlen(input);

	for (long i = 0; i < len; )
	{
		static std::vector<const char*> keywords;
		for (auto a : sget::CMDS::allCmd)
			keywords.emplace_back(a[0]);

		//static const char* controls[] = { "return", "if", "then", "else", NULL };
		//static const char* types[]    = { "int", "double", "char", "void", NULL };
		long tlen;  // token length
		if ((tlen = ic_match_any_token(input, i, &ic_char_is_idletter, keywords.data())) > 0)
		{
			ic_highlight(henv, i, tlen, "keyword"); 
			i += tlen;
		}
		/*else if ((tlen = ic_match_any_token(input, i, &ic_char_is_idletter, controls)) > 0)
		{
			ic_highlight(henv, i, tlen, "control"); // html color (or use the `control` style)
			i += tlen;
		}*/
		else if ((tlen = strlen(input+i) - strlen(strchr(input+i, ' '))) > 0)
		{
			ic_highlight(henv, i, tlen, "type"); 
			i += tlen;
		}
		else if ((tlen = ic_is_token(input, i, &ic_char_is_digit)) > 0)
		{ // digits
			ic_highlight(henv, i, tlen, "number");
			i += tlen;
		}
		else if (ic_starts_with(input + i,"//"))
		{  // line comment
			tlen = 2;
			while (i+tlen < len && input[i+tlen] != '\n') { tlen++; }
				ic_highlight(henv, i, tlen, "comment"); // or use a spefic color like "#408700"
				i += tlen;
		}
		else
		{
			ic_highlight(henv, i, 1, NULL);  // anything else (including utf8 continuation bytes)
			i++;
		}
	}
}

// MAIN

int main(int argc, char *argv[])
{
	sget::SnabbGET();
	sget::rw::Raw_mode(0, false);
	sget::io::io = sget::io::newIo(&ic_printf, &std::scanf);
	// To use: io << "foo"; io >> bar;
	
	setlocale(LC_ALL,"C.UTF-8");
	ic_set_history(NULL, 200);
	ic_set_default_completer(&completer, NULL);
	ic_set_default_highlighter(highlighter, NULL);
	ic_enable_auto_tab(true);
	ic_set_prompt_marker("", "|");

	system(""); // I don't kwon why I must put that, but if I don't add that,
				// escape codes don't work on Windows :(
	if (argc == 1 && !one_line)
	{
		sget::addToSCREEN(sget::init());
		// Printf is faster than std::cout and \n is faster than std::endl
		sget::io::io << sget::FRAME().c_str();
		char *line;

		while (true)
		{
			line = ic_readline(("\r\n" + sget::new_line()).c_str());

			sget::addToSCREEN(sget::new_line());
			sget::SCREEN.back() += std::string(line);
			sget::addToSCREEN(sget::read_input(std::string(line)));
			sget::io::io << sget::FRAME().c_str();

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

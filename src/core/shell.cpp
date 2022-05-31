// Core (main part)

/**
 * @file src/core/core.cpp
 * @brief Main part of the project.
 * @author LAPCoder
 * @version 0.0.0
 * 
 * MIT License
 */

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <Lmcons.h>

#include "shell.hpp"

SnabbGET::SnabbGET()
{
	dateOpen = std::time(0);
}

SnabbGET::~SnabbGET()
{
	std::cout << "Shell closed." << std::endl;
}

std::string SnabbGET::init()
{
	std::string msg = "\
       SnabbGET\n\
 Welcome to SnabbGET!\n\
Version: ";
	msg += VERSION;
	msg += "\n\
Copyright (c) LAPCoder\n\
----------------------\n";
	msg += new_line();
	return msg;
};

std::string SnabbGET::read_input(std::string input_user_t)
{
	input_user = input_user_t;

	historyFile.open("src/core/dist/.history.txt", std::ios_base::app);
	if (!historyFile.is_open())
	{
		std::cout << "Error opening file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	historyFile << input_user;
	historyFile << "\n";
	historyFile.close();
	if (input_user == "exit")
		return "Bye!\n";
	else if (input_user == "help")
		return "Commands:\n\
			   \texit - Exit the shell\n\
			   \thelp - Show this message\n\
			   \thelp <command> - Show help for <command>\n\
			   \tclear - Clear the screen\n\
			   \texe <command> - Execute a command of your OS (eg. gcc, npm, ls, dir...). Use it the same way as start.\n";
	else if (input_user == "clear")
		return "\033[2J\033[H";
	// Input start with "exe "?
	else if (input_user.substr(0, ((std::string)"exe ").size()) == "exe ")
	{
		system(input_user.substr(4).c_str());
		return "\n\033[92mCommand executed!\033[0m\n";
	}
	else if (input_user == "exe") return "You must specify a command to execute!\n";
	else return "Unknown command. Type 'help' for help.\n";
};

std::string SnabbGET::new_line()
{
	this->set_user_name();
	this->set_machine_name();
	
	std::string msg = "\033[96m";
	msg += this->userName;
	msg += "@";
	msg += this->computerName;
	msg += "\033[0m|> ";

	return msg;
};

void SnabbGET::set_user_name()
{
	#ifdef _WIN32
	
		TCHAR name [ UNLEN + 1 ];
		DWORD size = UNLEN + 1;

		if (GetUserName( (TCHAR*)name, &size ))
			this->userName = name;
		else
			this->userName = "guest";

	#else
		std::cout << "Not avilable for Linux & MacOS." << std::endl;
		this->userName = "guest";
	#endif
}

void SnabbGET::set_machine_name()
{
	#ifdef _WIN32
		std::string computerName = getenv("COMPUTERNAME");
		this->computerName = computerName;
	#else
		std::cout << "Not avilable for Linux & MacOS." << std::endl;
		this->computerName = "computer";
	#endif
}
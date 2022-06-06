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
#include <climits>
#include <unistd.h>

#ifdef _WIN32
	#include <windows.h>
	#include <Lmcons.h>
#endif

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

	historyFile.open("dist/.history.txt", std::ios_base::app);

	// Check the file
	if (!historyFile.is_open())
	{
		#ifdef DEBUG
			std::cout << "Error opening history file!" << std::endl;
		#endif

		// Try to create the file
		historyFile.open("dist/.history.txt", std::ios_base::out);
		if (!historyFile.is_open())
		{
			#ifdef DEBUG
				std::cout << "Error creating history file!" << std::endl;
			#endif

			// Use system() and to create the file
			system("mkdir dist");
			system("echo \"\" > dist/.history.txt");

			// Try to open the file again
			historyFile.open("dist/.history.txt", std::ios_base::app);
			if (!historyFile.is_open())
			{
				#ifdef DEBUG
					std::cout << "Error opening history file!" << std::endl;
				#endif
				
				exit(EXIT_FAILURE);
			}

		} else {
			historyFile.close();
			historyFile.open("dist/.history.txt", std::ios_base::app);
		}
	}
	historyFile << input_user;
	historyFile << "\n";
	historyFile.close();
	if (input_user == "exit")
		return "Bye!\n";
	else if (input_user == "help")
		return "Commands:\n\
	exit - Exit the shell\n\
	help - Show this message\n\
	help <command> - Show help for <command>\n\
	help --web - Show the web help\n\
	clear - Clear the screen\n\
	exe <command> - Execute a command of your OS (eg. gcc, npm, ls, dir...). Use it the same way as start.\n\
	\n\
	You don't find the parameters of a commmand? Write '<your command> -?'\n";
	else if (input_user == "clear" || input_user == "cls")
		return "\033[2J\033[H";
	// Input start with "exe "?
	else if (input_user.substr(0, ((std::string)"exe ").size()) == "exe ")
	{
		system(input_user.substr(4).c_str());
		return "\n\033[92mCommand executed!\033[0m\n";
	}
	else if (input_user == "exe") return "You must specify a command to execute!\n";
	else if (input_user == "help --web")
	{
		#ifdef _WIN32
			system("start https://snabbget.github.io/");
		#else
			system("xdg-open https://snabbget.github.io/");
		#endif
		return "\n\033[92mDocumentation opened!\033[0m\n";
	}
	else if (input_user == "") return new_line();
	else if (input_user.find("-?") != std::string::npos) return help_params(input_user.substr(0, input_user.find("-?")));
	else return "Unknown command. Type 'help' for help.\n";
};

std::string SnabbGET::new_line()
{
	this->set_user_name();
	this->set_machine_name();
	this->set_current_dir();
	
	std::string msg = "\033[1m\033[92m";
	msg += this->userName;
	msg += "@";
	msg += this->computerName;
	msg += "\033[39m:\033[96m";
	msg += this->currentDir;
	#ifdef DEBUG
		msg += "\033[93m [DEBUG]";
	#endif
	msg += "\033[95m |>\033[0m ";

	return msg;
};

void SnabbGET::set_user_name()
{
	this->userName = "guest";
	#ifdef _WIN32
	
		TCHAR name [UNLEN + 1];
		DWORD size = UNLEN + 1;

		if (GetUserName((TCHAR*)name, &size ))
			this->userName = name;
		else
		{
			#ifdef DEBUG
				std::cout << "Error getting user name on Windows!" << std::endl;
			#endif
		}

	#elif __linux__
		this->userName = getenv("USER");
		if (this->userName == "")
		{
			#ifdef DEBUG
				std::cout << "Error getting user name on Linux!" << std::endl;
			#endif
		}

	#else 
		#ifdef DEBUG
			std::cout << "Get user name is not avilable for MacOS." << std::endl;
		#endif
		this->userName = "user";
	#endif
}

void SnabbGET::set_machine_name()
{
	this->computerName = "computer";
	#ifdef _WIN32
		//std::string computerName = getenv("COMPUTERNAME");
		this->computerName = getenv("COMPUTERNAME"); //this->computerName = computerName;
		if (this->computerName == "")
		{
			#ifdef DEBUG
				std::cout << "Error getting machine name on Windows!" << std::endl;
			#endif
		}
	#elif __linux__
		char hostname[HOST_NAME_MAX];
		if (gethostname(hostname, HOST_NAME_MAX) == 1)
		{
			#ifdef DEBUG
				std::cout << "Error getting machine name on Linux!" << std::endl;
			#endif
		}
		else this->computerName = hostname;
	#else
		#ifdef DEBUG
			std::cout << "Get machine name is not avilable for MacOS." << std::endl;
		#endif
	#endif
}

void SnabbGET::set_current_dir()
{
	this->currentDir = "";
	#ifdef _WIN32
		this->currentDir = getcwd(NULL, 0);
		#ifdef DEBUG
			std::cout << "Current dir: " << this->currentDir << std::endl;
		#endif
	#elif __linux__
		this->currentDir = getenv("PWD");
		// Minimify the path (if start of path is user home, replace it with ~)
		if (this->currentDir.substr(0, ((std::string)getenv("HOME")).size()) == getenv("HOME"))
			this->currentDir = "~" + this->currentDir.substr(((std::string)getenv("HOME")).size());

		#ifdef DEBUG
			std::cout << "Current dir: " << this->currentDir << std::endl;
		#endif
	#else
		#ifdef DEBUG
			std::cout << "Get current dir is not avilable for MacOS." << std::endl;
		#endif
	#endif
}

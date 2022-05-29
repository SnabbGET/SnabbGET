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
		
		/*#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			#include <windows.h>
			#define INFO_BUFFER_SIZE 32767
			TCHAR	infoBuf[INFO_BUFFER_SIZE];
			DWORD	bufCharCount = INFO_BUFFER_SIZE;

			// Get and display the name of the computer.
			if (!GetComputerName(infoBuf, &bufCharCount))
				printError(TEXT("GetComputerName")); 
			computerName = infoBuf; 

			// Get and display the user name.
			if(!GetUserName(infoBuf, &bufCharCount ) )
				printError(TEXT("GetUserName")); 
			userName = infoBuf;
		#elif __APPLE__
			#include <sys/utsname.h>
			struct utsname unameData;
			uname(&unameData);
			userName = unameData.sysname;
			computerName = unameData.nodename;
		#elif defined(__linux__) || defined(__linux) || defined(__unix__)
			


			#include <unistd.h>
			#include <limits.h>

			gethostname(computerName, HOST_NAME_MAX);
			getlogin_r(userName, LOGIN_NAME_MAX);
		#elif defined(_POSIX_VERSION)
			#include <unistd.h>
			#include <pwd.h>
			#include <sys/utsname.h>

			struct utsname unameData;
			uname(&unameData);
			userName = unameData.sysname;
			computerName = unameData.nodename;
		#else
			#error "Unknown compiler"
		#endif*/

};

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
\texe <command> - Execute a command of your OS (eg. gcc, npm, ls, dir...)\n";
	else if (input_user == "clear")
		return "\033[2J\033[H";
	// Input start with "exe "?
	else if (input_user.substr(0, ((std::string)"exe ").size()) == "exe ")
	{
		system(input_user.substr(4).c_str());
		return "\n\033[92mCommand executed!\033[0m\n";
	}
	else if (input_user == "exe")
		return "You must specify a command to execute!\n";
	else
		return "Unknown command. Type 'help' for help.\n";
};

std::string SnabbGET::new_line()
{
	std::string msg = "\033[96m";
	msg += userName;
	msg += "@";
	msg += computerName;
	msg += "\033[0m>>> ";
	return msg;
};
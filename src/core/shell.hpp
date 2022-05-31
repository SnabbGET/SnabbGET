#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdlib>

#define VERSION "0.0.0"

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
        // get user's name
        void set_user_name();
        // get user PC name
        void set_machine_name();

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
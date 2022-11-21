// Core (main part)

/*-------------------------------------------------
 * ------------------************------------------
 * -----------------**************-----------------
 * ----------------****************----------------
 * ---------------********--********---------------
 * --------------********----********--------------
 * -------------********--##--********-------------
 * ------------********---##---********------------
 * -----------********----##----********-----------
 * ----------********-----##-----********----------
 * ---------********------##------********---------
 * --------********-------##-------********--------
 * -------********--------##--------********-------
 * ------********--------------------********------
 * -----********----------------------********-----
 * ----********-----------##-----------********----
 * ---********------------##------------********---
 * --********************************************--
 * -**********************************************-
 * ************************************************
 * -                                              -
 * -  USE ALWAYS CRLF (\r\n) TO ENTER A NEW LINE  -
 * -            Don't use "std::endl"             -
 * -  ==========================================  -
 * -                                              -
 *##  ## ###### ######   ###### ###### ##     ######
 *##  ## ##     ##       ##     ##  ## ##     ##    
 *##  ## ###### ######   ##     ###### ##     ######
 *##  ##     ## ##       ##     ## ##  ##     ##
 *###### ###### ######   ###### ##  ## ###### ##
 *       It can be read on a mini-map ;D
 */

/**
 * @file src/core/core.cpp
 * @brief Main part of the project.
 * @author LAPCoder
 * @version 0.1.0
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
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <unistd.h>
#ifdef __linux__
	#include <termios.h>
#endif
#include <functional>

#ifdef _WIN32
	#include <windows.h>
	#include <Lmcons.h>
#endif

/* ####### ##   ## ##   ##  ###### ####### #######  #####  ##   ##  ######
 * ##      ##   ## ###  ## ###       ###     ###   ### ### ###  ## ##
 * ##      ##   ## #### ## ##        ###     ###   ##   ## #### ##   ##
 * ####### ##   ## ## #### ##        ###     ###   ##   ## ## ####    ##
 * ##      ### ### ##  ### ###       ###     ###   ### ### ##  ###      ##
 * ##       #####  ##   ##  ######   ###   #######  #####  ##   ## ######
 */

void SnabbGET::SnabbGET()
{
	dateOpen = std::time(0);
	init();
}

void SnabbGET::SnabbGET(bool cmd_line)
{
	SnabbGET();
	CMD_LINE = cmd_line;
}

std::string SnabbGET::init()
{
	CMDS::CMDS();
	set_current_dir();
	std::string msg = htmlToRgbEsc("#ff0000", true) + "\r\
       SnabbGET\r\n\033[0m\
 Welcome to SnabbGET!\r\n\
Version: ";
	msg += VERSION;
	msg += "\r\n\
Copyright (c) SnabbGET\r\n\
Under the  MIT License\r\n\
----------------------\r\n";
	msg += "\033[1A\r\n";
	msg += new_line();
	return msg;
}

void SnabbGET::get_command(std::string input_user_t)
{
	std::string tmp = "";
	size_t j = 0;
	ZERO_ANY(std::string, cmd, MAX_INPUT);

	for (int i = 0; i < (int)input_user_t.length(); i++)
		if (input_user_t[i] != ' ')
			tmp += input_user_t[i];
		else if (tmp != "")
		{
			cmd[j++] = tmp;
			tmp = "";
		}
	if (tmp != "") cmd[j++] = tmp;
	cmdLen = j;
}

std::string SnabbGET::FRAME()
{
	std::string tmp = join(SCREEN, "\r\n");
	tmp.pop_back(); tmp.pop_back();
	return std::string("\033[J\033[2J\033[3J\033[H") + tmp;
}

std::string SnabbGET::runCmd(
	int id, std::string cmd[], int cmdLen,
	std::string input_user
)
{
	auto &cmdTmp = SnabbGET::CMDS::cmdLst[id];
	return cmdTmp(cmd, cmdLen, input_user);
}

std::string SnabbGET::read_input(std::string input_user_t)
{
	input_user = input_user_t;

	get_command(input_user);

	#ifdef DEBUG
		/*std::cout << "\r\nCommand: [";
		for (unsigned int i = 0; i < cmdLen; i++)
			std::cout << cmd[i] << ", ";
		std::cout << "]" << "\r\n" << "Input: " << input_user
			<< "\r\n" << "CmdLen: " << cmdLen << "\r\n";*/
	#endif

	//std::cout << &cmd << std::endl;
	if (! one_line)
	{
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

				// Use system() to create the file
				system("mkdir dist");
				system("echo \"\" > dist/.history.txt");

				// Try to open the file again
				historyFile.open("dist/.history.txt", std::ios_base::app);
				if (!historyFile.is_open())
				{
					#ifdef DEBUG
						std::cout << "Error opening history file!" <<std::endl;
					#endif
					
					exit(EXIT_FAILURE);
				}

			}
			else
			{
				historyFile.close();
				historyFile.open("dist/.history.txt", std::ios_base::app);
			}
		}
		historyFile << input_user;
		historyFile << "\r\n";
		historyFile.close();
	}

	if (cmdLen == 0) return "";

/*  ######  #####  ##   ## ##   ##   ###   ##   ## #####    ######
 * ###     ### ### ### ### ### ###  ## ##  ###  ## ##   ## ##
 * ##      ##   ## ####### ####### ##   ## #### ## ##   ##   ##
 * ##      ##   ## ## # ## ## # ## ####### ## #### ##   ##    ##
 * ###     ### ### ##   ## ##   ## ##   ## ##  ### ##   ##      ##
 *  ######  #####  ##   ## ##   ## ##   ## ##   ## #####   ###### 
 */

	//Check if 'cmd' contain '-?'
	else if (cmd[0] != "exe" && contain(cmd, cmdLen, "-?"))
		return help_params(cmd[0]);

	// Exit
	else if (cmd[0] == "exit")
		return runCmd(EXIT, cmd, cmdLen, input_user);

	// Help
	else if (cmd[0] == "help")
		return runCmd(HELP, cmd, cmdLen, input_user);

	// Clear
	else if (cmd[0] == "clear" || cmd[0] == "cls")
		return runCmd(CLS,  cmd, cmdLen, input_user);

	// Say (echo)
	else if (cmd[0] == "say" || cmd[0] == "echo")
		return runCmd(SAY,  cmd, cmdLen, input_user);

	// Cd
	else if (cmd[0] == "cd")
		return runCmd(CD,   cmd, cmdLen, input_user);

	// Execute
	else if (cmd[0] == "exe" && cmdLen > 1)
		return runCmd(EXE,  cmd, cmdLen, input_user);
	else if (cmd[0] == "exe" && cmdLen == 1)
		return "You must enter a command!\r\n";

	// Ls
	else if (cmd[0] == "ls")
		return runCmd(LS,  cmd, cmdLen, input_user);

	// Cp
	else if (cmd[0] == "cp")
		return runCmd(CP,  cmd, cmdLen, input_user);

	// Mv
	else if (cmd[0] == "mv")
		return runCmd(MV,  cmd, cmdLen, input_user);

	// Mk
	else if (cmd[0] == "mk")
		return runCmd(MK,  cmd, cmdLen, input_user);

	// Rm
	else if (cmd[0] == "rm")
		return runCmd(RM,  cmd, cmdLen, input_user);

	else if (*(cmd[0].begin()) == '.' || *(cmd[0].begin()) == '/')
	{
		std::ifstream f;
		f.open(cmd[0]);
		if (!f)
			return "File not found!";
		else
		{
			std::string r[0];
			return runCmd(EXE, r, 0, "exe " + input_user);
		}
	}

	// Check PATH
	else
	{
		try
		{
			// F*ck the for
			for (std::string a : split(PATH, ':'))
			{
				std::ifstream f;
				f.open(a + "/" + cmd[0]);
				if (!f)
					std::cout << "\r\nFile not found!";
				else
				{
					std::string r[0];
					return runCmd(EXE, r, 0, std::string("exe " + input_user));
				}
			}
		}
		catch (std::out_of_range &e)
		{
			return std::string("Error: out of range: ") + e.what();
		}

		//std::cout << split(PATH, ":");
	
		// Not found
		return "Command not found!";
	}
}

std::string SnabbGET::new_line()
{
	set_user_name();
	set_machine_name();
	set_current_dir();
	
	/*std::string msg = "\033[1m\033[92m";
	msg += userName;
	msg += "@";
	msg += computerName;
	msg += "\033[39m:\033[96m";
	msg += currentDir;
	#ifdef DEBUG
		msg += "\033[93m [DEBUG]";
	#endif
	msg += "\033[95m |>\033[0m ";

	#ifdef __linux__
		msg += "\033[1A\n";
	#endif
	return msg;*/
	return promptSettings();
}

void SnabbGET::set_user_name()
{
	userName = "guest";
	#ifdef _WIN32
	
		TCHAR name [UNLEN + 1];
		DWORD size = UNLEN + 1;

		if (GetUserName((TCHAR*)name, &size ))
			userName = name;
		else
		{
			#ifdef DEBUG
				std::cout << "Error getting user name on Windows!" <<std::endl;
			#endif
		}

	#elif __linux__
		userName = getenv("USER");
		if (userName == "")
		{
			#ifdef DEBUG
				std::cout << "Error getting user name on Linux!" << std::endl;
			#endif
		}

	#else 
		#ifdef DEBUG
			std::cout << "Get user name is not avilable for MacOS."<<std::endl;
		#endif
		userName = "user";
	#endif
}

void SnabbGET::set_machine_name()
{
	computerName = "computer";
	#ifdef _WIN32
		//std::string computerName = getenv("COMPUTERNAME");
		computerName = getenv("COMPUTERNAME");
		if (computerName == "")
		{
			#ifdef DEBUG
				std::cout<<"Error getting machine name on Windows!"<<std::endl;
			#endif
		}
	#elif __linux__
		char hostname[HOST_NAME_MAX];
		if (gethostname(hostname, HOST_NAME_MAX) == 1)
		{
			#ifdef DEBUG
				std::cout << "Error getting machine name on Linux!"<<std::endl;
			#endif
		}
		else computerName = hostname;
	#else
		#ifdef DEBUG
			std::cout  << "Get machine name is not avilable for MacOS."
				<< std::endl;
		#endif
	#endif
}

void SnabbGET::set_current_dir()
{ //USE PWD COMMAND
	currentDir = "/";
	#ifdef _WIN32
		currentDir = getcwd(NULL, 0);
		#ifdef DEBUG
			std::cout << "Current dir: " << currentDir << std::endl;
		#endif
	#elif __linux__
		currentDir = getenv("PWD");
		// Minimify the path (if start of path is user home, replace it with ~)
		if (currentDir.substr(0,
				((std::string)getenv("HOME")).size()
			) == getenv("HOME")
		)
			currentDir = "~" + currentDir.substr(
				((std::string)getenv("HOME")).size()
			);

		#ifdef DEBUG
			//std::cout << "Current dir: " << this->currentDir << std::endl;
		#endif
	#else
		#ifdef DEBUG
			std::cout<<"Get current dir is not avilable for MacOS."<<std::endl;
		#endif
	#endif
}

/* Initialize new terminal i/o settings */

/* ######  ## # ##
 * ##   ## ## # ##
 * ######  ##,#,##
 * ## ##   #######
 * ##  ##   #####
 * ##   ##  ## ##
 */

void SnabbGET::Raw_mode::Raw_mode(int echo)
{
	#ifdef __linux__
		// grab old terminal i/o settings
		tcgetattr(0, &SnabbGET::Raw_mode::old);
		// make new settings same as old settings
		SnabbGET::Raw_mode::new1 = SnabbGET::Raw_mode::old;
		// disable buffered i/o
		SnabbGET::Raw_mode::new1.c_lflag &= ~ICANON;
		// set echo mode
		SnabbGET::Raw_mode::new1.c_lflag &= echo ? ECHO : ~ECHO;
		// disable output processing
		SnabbGET::Raw_mode::new1.c_oflag &= ~(OPOST);
		// use these new terminal i/o settings now
		tcsetattr(0, TCSANOW, &SnabbGET::Raw_mode::new1);
	#endif
	if (echo) {}
	// /o o\ ?
	// \---/  Hum...
}

void SnabbGET::Raw_mode::Raw_mode()
{
	#ifdef __linux__
		// grab old terminal i/o settings
		tcgetattr(0, &SnabbGET::Raw_mode::old);
		// make new settings same as old settings
		SnabbGET::Raw_mode::new1 = SnabbGET::Raw_mode::old;
		// disable buffered i/o
		SnabbGET::Raw_mode::new1.c_lflag &= ~ICANON;
		// set echo mode
		SnabbGET::Raw_mode::new1.c_lflag &= ~ECHO;
		// disable output processing
		SnabbGET::Raw_mode::new1.c_oflag &= ~(OPOST);
		// use these new terminal i/o settings now
		tcsetattr(0, TCSANOW, &SnabbGET::Raw_mode::new1);
	#endif
}

void SnabbGET::Raw_mode::pause()
{
	#ifdef __linux__
		tcsetattr(0, TCSANOW, &SnabbGET::Raw_mode::old);
	#endif
}

void SnabbGET::Raw_mode::resume()
{
	#ifdef __linux__
		tcsetattr(0, TCSANOW, &SnabbGET::Raw_mode::new1);
	#endif
}

void SnabbGET::CMDS::CMDS()
{
	cmdLst.emplace_back(_exit_);
	cmdLst.emplace_back(_help_);
	cmdLst.emplace_back(_cls_ );
	cmdLst.emplace_back(_say_ );
	cmdLst.emplace_back( _cd_ );
	cmdLst.emplace_back(_exe_ );
	cmdLst.emplace_back( _ls_ );
	cmdLst.emplace_back( _cp_ );
	cmdLst.emplace_back( _mv_ );
	cmdLst.emplace_back( _mk_ );
	cmdLst.emplace_back( _rm_ );

	allCmd.emplace_back("exit");
	allCmd.emplace_back("help");
	allCmd.emplace_back("cls" );
	allCmd.emplace_back("say" );
	allCmd.emplace_back( "cd" );
	allCmd.emplace_back("exe" );
	allCmd.emplace_back( "ls" );
	allCmd.emplace_back( "cp" );
	allCmd.emplace_back( "mv" );
	allCmd.emplace_back( "mk" );
	allCmd.emplace_back( "rm" );
}

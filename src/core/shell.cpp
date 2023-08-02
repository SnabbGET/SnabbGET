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

//#ifndef SNABBGET_CORE_CPP
//#define SNABBGET_CORE_CPP

#include "shell.hpp"

/* ####### ##   ## ####### #######
 *   ###   ###  ##   ###     ###
 *   ###   #### ##   ###     ###
 *   ###   ## ####   ###     ###
 *   ###   ##  ###   ###     ###
 * ####### ##   ## #######   ###
 */

#ifdef __EMSCRIPTEN__
	/*extern*/ bool SnabbGET::one_line = true;
#else
	/*extern*/ bool SnabbGET::one_line = false;
#endif

#ifdef NO_RL
	#warning Readline dislabed!
#endif
/*extern*/ std::string SnabbGET::userName = "User";

/*extern*/ std::string SnabbGET::computerName = "Computer";
/*extern*/ std::string SnabbGET::currentDir = "/";
/*extern*/ bool SnabbGET::CMD_LINE = false;

/*extern*/ std::string SnabbGET::cmd[MAX_INPUT] = {(std::string)""};
/*extern*/ unsigned SnabbGET::cmdLen = 0;
/*extern*/ std::string SnabbGET::input_user = "";
/*extern*/ std::time_t SnabbGET::dateOpen = std::time(0);
/*extern*/ unsigned short SnabbGET::tabOpen = 1;
/*extern*/ char *SnabbGET::oldLine = (char*)"";

/*extern*/ std::vector<std::string> SnabbGET::SCREEN = (std::vector<std::string>){};

/*extern*/ std::vector<
	std::function<
		std::string(std::string[], int&, std::string&)
	>
> SnabbGET::CMDS::cmdLst =
	std::vector<std::function<std::string(std::string[], int&, std::string&)>>();
/*extern*/ std::vector<std::vector<const char*>> SnabbGET::CMDS::allCmd =
	(std::vector<std::vector<const char*>>){};

extern int (*SnabbGET::io::newIo::outFunct)(const char *, ...);
extern int (*SnabbGET::io::newIo:: inFunct)(const char *, ...);

/*extern*/ bool SnabbGET::Raw_mode::on = true;

/*extern*/ const std::string SnabbGET::io::endl = "\r\n";

void SnabbGET::addToSCREEN(std::string txt)
{
	SCREEN.emplace_back(txt);
	if (SCREEN.size() > MAX_SCREEN_ELEMENTS)
		SCREEN.erase(SCREEN.begin());
}

SnabbGET::io::newIo::newIo() {}
// Constructor with the funtion in param
SnabbGET::io::newIo::newIo(int (o)(const char *, ...),
	int (i)(const char *, ...)) {outFunct = o; inFunct = i;}
// Destructor
SnabbGET::io::newIo::~newIo() {}

template<class T> inline SnabbGET::io::newIo &SnabbGET::io::operator<<(
	SnabbGET::io::newIo &exp, T &arg)
{
	exp.outFunct(arg); // TODO: test with int
	return exp;
}

inline SnabbGET::io::newIo &SnabbGET::io::operator<<(
	SnabbGET::io::newIo &exp, SnabbGET::io::stdEndl)
// std::endl is a pointer
{
	exp.outFunct(endl.c_str());
	return exp;
}

inline SnabbGET::io::newIo &SnabbGET::io::operator<<(
	SnabbGET::io::newIo &exp, std::string &arg)
{
	exp.outFunct(arg.c_str());
	return exp;
}

template<class T> inline SnabbGET::io::newIo &SnabbGET::io::operator>>(
	SnabbGET::io::newIo &exp, T &arg)
{
	std::string r = "%c";
		 if (typeid(T) == typeid(int)) r = "%d";
	else if (typeid(T) == typeid(char)) r = "%c";
	else if (typeid(T) == typeid(signed char)) r = "%c";
	else if (typeid(T) == typeid(unsigned char)) r = "%c";
	else if (typeid(T) == typeid(float)) r = "%f";
	else if (typeid(T) == typeid(double)) r = "%lf";
	else if (typeid(T) == typeid(long double)) r = "%Lf";
	else if (typeid(T) == typeid(short)) r = "%hd";
	else if (typeid(T) == typeid(unsigned)) r = "%u";
	else if (typeid(T) == typeid(long)) r = "%li";
	else if (typeid(T) == typeid(long long)) r = "%lli";
	else if (typeid(T) == typeid(unsigned long)) r = "%lu";
	else if (typeid(T) == typeid(unsigned long long)) r = "%llu";
	exp.inFunct(r.c_str(), &arg);
	return exp;
}
inline SnabbGET::io::newIo &SnabbGET::io::operator>>(
	SnabbGET::io::newIo &exp, std::string &arg)
{
	exp.inFunct("%s", arg.c_str());
	return exp;
}

// WARNING!!!!! THOSE LINES MUST STAY LIKE THAT!!!
//                          ====
#include "other/errors.cpp"
//#include "./includesAll.hpp"
#include "./settings/reader.cpp"
#include "./cli/cli.cpp"

/**
 * @file src/core/core.cpp
 * @brief Main part of the project.
 * @author LAPCoder
 * @version 0.2.0
 * 
 * MIT License
 */

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdio>
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
#include <vector>
#include <thread>

#ifdef _WIN32
	#include <windows.h>
	#include <Lmcons.h>
#endif

#define READLINE_LIBRARY

#include "../../include/readline/readline.h"
#include  "../../include/readline/history.h"

/* ####### ##   ## ##   ##  ###### ####### #######  #####  ##   ##  ######
 * ##      ##   ## ###  ## ###       ###     ###   ### ### ###  ## ##
 * ##      ##   ## #### ## ##        ###     ###   ##   ## #### ##  ###
 * ####### ##   ## ## #### ##        ###     ###   ##   ## ## ####    ###
 * ##      ### ### ##  ### ###       ###     ###   ### ### ##  ###      ##
 * ##       #####  ##   ##  ######   ###   #######  #####  ##   ## ######
 */

void SnabbGET::SnabbGET()
{
	#if __cplusplus < 201703L
		/*printf("\033[J\033[2J\033[3J\033[H\033[41m\033[1m"
			 "<ERRO R>: THIS C++ VERSION IS UNSUPPORTED BY SNABBGET\033[0m\r\n");
			 */

		THROW_ERR(err::BAD_VERSION);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	#endif

	atexit((void(*)())[](){
		SCREEN.clear();
		free(oldLine);
	});

	dateOpen = std::time(0);
	init();

	#ifndef NO_RL
		init_rl();
	#endif

	// Output function
	SnabbGET::io::newIo::outFunct = &std::printf;
	SnabbGET::io::newIo::inFunct = &std::scanf;
	
	CMDS::CMDS();
	set_current_dir();
}

void SnabbGET::SnabbGET(bool cmd_line)
{
	SnabbGET();
	CMD_LINE = cmd_line;
}

int SnabbGET::rlKeysFuncs(
	int, int
#ifndef NO_RL
	key
#endif
	)
{
	#ifndef NO_RL
		rl_insert_text(key == '(' ? "()" :
					(key == '"' ? "\"\"":
					(key == '[' ? "[]":
					(key == '\''? "''":
					(key == '{' ? "{}": "``")))));
		rl_point--; // TODO: Optimize
	#endif
	return 0;
}

std::string SnabbGET::init()
{
	std::string msg = htmlToRgbEsc("#ff0000", true) + "\r\
       SnabbGET\r\n\033[0m\
 Welcome to SnabbGET!\r\n\
Version: ";
	msg += VERSION;
	msg += "\r\n\
Copyright (c) SnabbGET\r\n\
Under the  MIT License\r\n\
Type 'help'  for infos\r\n\
──────────────────────";
	//msg += "\033[1A\r\n";
	//msg += new_line();
	return msg;
}

void SnabbGET::init_rl()
{
	rl_command_func_t rlKeysFuncs;
	rl_bind_key('"', rlKeysFuncs);
	rl_bind_key('\'',rlKeysFuncs);
	rl_bind_key('(', rlKeysFuncs);
	rl_bind_key('[', rlKeysFuncs);
	rl_bind_key('{', rlKeysFuncs);
	rl_bind_key('`', rlKeysFuncs);
	rl_bind_key(4, [](int, int)->int {
		printf("\n%s", SnabbGET::read_input("exit").c_str());
		exit(EXIT_SUCCESS);
		return 0;
	});
	rl_bind_key(3, [](int, int)->int {
		printf("\n%s", SnabbGET::read_input("exit").c_str());
		exit(EXIT_SUCCESS);
		return 0;
	});
	rl_bind_key('\t', [](int, int)->int {
		printf("%s", sget::FRAME().c_str());
		//printf("\n%s | %s", rl_line_buffer, oldLine);
		rl_forced_update_display();
		if (strcmp(rl_line_buffer, oldLine) == 0)
		{
			tabOpen++;
			tabOpen %= 3;
		}
		if (tabOpen != 1)
		{
			std::vector<std::string> tmp;
			for (auto i : CMDS::allCmd)
			{
				std::string s;
				if (tabOpen == 2)
					s = std::string(i[0]);
				else
					s = std::string(i[0]) + " " + std::string(i[1]);
				if ((s.substr(0, strlen(rl_line_buffer)) == rl_line_buffer) &&
					(std::find(tmp.begin(), tmp.end(), s)) == tmp.end())
					tmp.emplace_back(s);
			}
			int posX, posY;
			get_pos(&posY, &posX);
			if (tmp.size() > 0)
			{
				if (tmp.size()+3 <= (long unsigned)posY)
					CLI::list(posX, posY-tmp.size() - 2, tmp);
				else
					CLI::list(posX, posY+1, tmp);
			}
			else
			{
				for (auto i : CMDS::allCmd)
				{
					std::string s;
					if (tabOpen == 2)
						s = std::string(i[0]);
					else
						s = std::string(i[0]) + " " + std::string(i[1]);
					if (std::find(tmp.begin(), tmp.end(), std::string(s))
						== tmp.end())
						tmp.emplace_back(s);
				}
				if (tmp.size()+3 <= (long unsigned)posY)
					CLI::list(posX, posY-tmp.size() - 2, tmp);
				else
					CLI::list(posX, posY+1, tmp);
			}
			if (tmp.size() == 1)
			{
				std::vector<std::string> tmp2;
				for (auto i : CMDS::allCmd)
				{
					std::string s = std::string(i[0]);
					if ((s.substr(0, strlen(rl_line_buffer)) == rl_line_buffer) &&
						(std::find(tmp2.begin(), tmp2.end(), s)) == tmp2.end())
						tmp2.emplace_back(s);
				}
				rl_insert_text((tmp2[0].substr(strlen(rl_line_buffer)) + " ")
					.c_str());
			}
		}
		oldLine = (char *) malloc(strlen(rl_line_buffer)+1);
		snprintf(oldLine, strlen(rl_line_buffer)+1, "%s", rl_line_buffer);
		return 0;
	});
	/*rl_bind_key (27, rlKeysFuncs); //ascii code for ESC
	rl_bind_keyseq ("\\C-a", rlKeysFuncs);*/
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

	if (cmdLen == 0) return "\033[1A";

/*  ######  #####  ##   ## ##   ##   ###   ##   ## #####    ######
 * ###     ### ### ### ### ### ###  ## ##  ###  ## ##   ## ##
 * ##      ##   ## ####### ####### ##   ## #### ## ##   ##   ##
 * ##      ##   ## ## # ## ## # ## ####### ## #### ##   ##    ##
 * ###     ### ### ##   ## ##   ## ##   ## ##  ### ##   ##      ##
 *  ######  #####  ##   ## ##   ## ##   ## ##   ## #####   ###### 
 */

	// TODO: use std::find(allCmds[0])

	//Check if 'cmd' contain '-?'
	else if (cmd[0] != "exe" && contain(cmd, cmdLen, "-?") && cmd[0] != "-?")
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
		return "You must enter a command!";

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

	// Calc
	else if (cmd[0] == "calc")
		return runCmd(CALC,cmd, cmdLen, input_user);

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
				if (!f){}
					//std::cout << "\r\nFile not found!";
				else
				{
					std::string r[0];
					return runCmd(EXE, r, 0, std::string("exe " + input_user));
				}
			}
		}
		catch (std::out_of_range &e)
		{
			THROW_ERR_MSG(err::VAR_OUT_OF_RANGE, (char*)e.what());
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
			//std::cout << "Erro r getting user name on Windows!" <<std::endl;
				THROW_ERR_MSG(err::GET_PATH_USR, (char*)"On Windows;");
			#endif
		}

	#elif __linux__
		userName = getenv("USER");
		if (userName == "")
		{
			#ifdef DEBUG
				//std::cout << "Erro r getting user name on Linux!" << std::endl;
				THROW_ERR_MSG(err::GET_PATH_USR, (char*)"On Linux;");
			#endif
		}

	#else 
		#ifdef DEBUG
		//std::cout << "Get user name is not avilable for MacOS."<<std::endl;
			THROW_ERR_MSG(err::GET_PATH_USR, (char*)"Not available on MacOS;");
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
			//std::cout<<"Erro r getting machine name on Windows!"<<std::endl;
				THROW_ERR_MSG(err::GET_PATH_CMPUT, (char*)"On Windows;");
			#endif
		}
	#elif __linux__
		char hostname[HOST_NAME_MAX];
		if (gethostname(hostname, HOST_NAME_MAX) == 1)
		{
			#ifdef DEBUG
			//std::cout << "Erro r getting machine name on Linux!"<<std::endl;
				THROW_ERR_MSG(err::GET_PATH_CMPUT, (char*)"On Linux;");
			#endif
		}
		else computerName = hostname;
	#else
		#ifdef DEBUG
			//std::cout  << "Get machine name is not avilable for MacOS."
				//<< std::endl;
		   THROW_ERR_MSG(err::GET_PATH_CMPUT, (char*)"Not available on MacOS;");
		#endif
	#endif
}

void SnabbGET::set_current_dir()
{
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
		//std::cout<<"Get current dir is not avilable for MacOS."<<std::endl;
			THROW_ERR_MSG(err::GET_PATH_PWD, (char*)"Not available on MacOS;");
		#endif
	#endif
	#ifndef NO_RL
		rl_set_prompt(promptSettings().c_str());
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

void SnabbGET::Raw_mode::Raw_mode(int
	/*#ifdef __linux__
		echo
	#endif*/
	, bool enlabed)
{
	on = enlabed;
	#ifdef __linux__
		// grab old terminal i/o settings
		tcgetattr(0, &SnabbGET::Raw_mode::old);
		// make new settings same as old settings
		SnabbGET::Raw_mode::new1 = SnabbGET::Raw_mode::old;
		if (on)
		{
			// disable buffered i/o
			//SnabbGET::Raw_mode::new1.c_lflag &= ~ICANON;
			// set echo mode
			//SnabbGET::Raw_mode::new1.c_lflag &= echo ? ECHO : ~ECHO;
			// disable output processing
			//SnabbGET::Raw_mode::new1.c_oflag &= ~(OPOST);
			SnabbGET::Raw_mode::new1.c_lflag &= ~ISIG;
			// use these new terminal i/o settings now
			tcsetattr(0, TCSANOW, &SnabbGET::Raw_mode::new1);
		}
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
	cmdLst.emplace_back(_calc_);

	typedef std::vector<const char*> a;
	allCmd.emplace_back((a){"exit", ""});
	allCmd.emplace_back((a){"help", "[--web]"});
	allCmd.emplace_back((a){"cls" , ""});
	allCmd.emplace_back((a){"say" , "/ echo [txt]"});
	allCmd.emplace_back((a){ "cd" , "[-p]"});
	allCmd.emplace_back((a){"exe" , "cmd"});
	allCmd.emplace_back((a){ "ls" , "[path]"});
	allCmd.emplace_back((a){ "cp" , "src dst"});
	allCmd.emplace_back((a){ "mv" , "src dst"});
	allCmd.emplace_back((a){ "mk" , "[-d] file"});
	allCmd.emplace_back((a){ "rm" , "file"});
	allCmd.emplace_back((a){"calc", "expression"});
}

//#endif

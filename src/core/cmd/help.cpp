// Help command

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

//#include "../shell.hpp"

/**
 * @brief Help command
 * 
 * @param cmd The commands in array
 * @param cmdLen The commands' array lenght
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_help_(std::string cmd[], int cmdLen, std::string)
{
	// Yes, it's bad to use a help function to debug...
	//return join(SCREEN, "\r\n");
	if (contain(cmd, cmdLen, "--web"))
	{
		#ifdef _WIN32
			system("start https://snabbget.github.io/");
		#else
			system("xdg-open https://snabbget.github.io/");
		#endif

		// DEBUG: Success Webpage opened
		#ifdef DEBUG
			return "\r\n\033[92mWeb page opened!\033[0m\r\n";
		#else
			return "";
		#endif
	}
	else
		return "\
Commands:\r\n\
	say,\r\n\
	echo               - Write something\r\n\
	cd [<dir>]         - Change Directory\r\n\
	exit               - Exit the shell\r\n\
	help [--web]       - Show this message\r\n\
	clear,\r\n\
	cls                - Clear the screen\r\n\
	exe <command>      - Execute a command of your OS (eg. gcc, npm, ls, dir...). Use it the same way as start.\r\n\
	ls                 - List file and dirs in the current directory\r\n\
	cp <file> <tofile> - Copy a file or a dir in an other file or a dir\r\n\
	mv <file> <tofile> - Move (or rename) a file or a dir to an other dir\r\n\
	mk <file>          - Create a file\r\n\
	rm <file>          - Remove a file\r\n\
\r\n\
You don't find the parameters of a commmand? Write '<your command> -?'\r\n";
}

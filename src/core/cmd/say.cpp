// Say command

#include "../shell.hpp"

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
 * @brief Say command
 * 
 * @param cmd The user command in array
 * @param cmdLen [NOT USED]
 * @param input_user The user input
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_say_(std::string cmd[],int&, std::string &input_user)
{
	if (input_user.length() < cmd[0].length()+1) return "";
	else return input_user.substr(cmd[0].length()+1);
}

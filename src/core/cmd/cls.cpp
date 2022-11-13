// Clear command

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
 * @brief Clear command
 * 
 * @param cmd [NOT USED]
 * @param cmdLen [NOT USED]
 * @param input_user [NOT USED]
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_cls_(std::string[], int, std::string)
{
	SCREEN.clear();
	return "\033[J\033[2J\033[3J\033[H";
}

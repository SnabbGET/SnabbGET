#pragma once

#include <iostream>
#include <string>

std::string getdate();
std::string gettime();
std::string help_params(std::string cmd);
bool contain(std::string *lst, unsigned int lstLen, std::string tfind);

#ifdef FILEENUMERR
	#include "utils.cpp"
#endif

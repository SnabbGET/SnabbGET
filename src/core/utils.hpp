#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>

std::string getdate();
std::string gettime();
std::string help_params(std::string cmd);
bool contain(std::string *lst, unsigned int lstLen, std::string tfind);
std::string hexToDec(std::string num);
std::string htmlToRgbEsc(std::string htmlColor, int isForeground);
std::string exec(const char* cmd);
std::string concatArr(std::string *arr, int N);

#ifdef FILEENUMERR
	#include "utils.cpp"
#endif

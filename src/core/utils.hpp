#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>

std::string getdate();
std::string gettime();
std::string help_params(std::string cmd);
bool contain(std::string *lst, unsigned int lstLen, std::string tfind);
std::string hexToDec(std::string num);
std::string htmlToRgbEsc(std::string htmlColor, int isForeground);
std::string exec(const char* cmd);
std::string concatArr(std::string *arr, int N);
std::string replaceAll(std::string str, const std::string &from,
						const std::string &to);
std::string join(std::vector<std::string> const &strings, const char *delim);
std::vector<std::string> split(const std::string &str, const char &token);

#ifdef FILEENUMERR
	#include "utils.cpp"
#endif

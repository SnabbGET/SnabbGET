#pragma once

#ifndef SNABBGET_UTILS
#define SNABBGET_UTILS

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#ifdef __WIN32
	#include <windows.h>
#else
	#include <termios.h>
#endif

std::string getdate();
std::string gettime();
std::string help_params(std::string cmd);
bool contain(std::string *lst, unsigned int lstLen, std::string tfind);
std::string hexToDec(std::string num);
std::string htmlToRgbEsc(std::string htmlColor, int isForeground);
std::string exec(const char* cmd);
std::string concatArr(std::string arr[], int N);
std::string replaceAll(std::string str, const std::string &from,
						const std::string &to);
std::string join(std::vector<std::string> const &strings, const char *delim);
std::vector<std::string> split(const std::string &str, const char &token);
int get_pos(int *y, int *x);
bool is_number(const std::string& s);

#endif

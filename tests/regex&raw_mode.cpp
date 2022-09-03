#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>
#include <cstdio>
#include <regex>
#include "../src/core/shell.hpp"

SnabbGET sget;
SnabbGET::Raw_mode rw(0);

std::regex reg("[A-z]\b|" + std::to_string(rw.DEL_KEY) + "[A-z]");

std::string del(std::string str)
{
	std::string str1 = std::regex_replace(str, reg, "$2");
	str1 = std::regex_match(str1, reg) == 0 ? str1 : del(str1);
	return str1;
}

int main()
{
	while (true)
	{
		char c = '\0';
		std::string input_user = "";


		//int right_count = 0;

		// Not really char count, but the number of chars left to read
		//int chars_count = 0;

		// Use the Raw mode to read the input from the user
		// and hide escape sequences (e.g. ^[[A).
		while (1)
		{
			//std::string input_user_tmp = "";
			read(0, &c, 1);
			if (c == '\n') break;
			if (((32  <= (int)c) && 
					(126 >= (int)c)) || 
				((161 <= (int)c) &&
					(255 >= (int)c)) ||
				c == rw.TAB)
				{
					input_user += c;
					//input_user_tmp = c;
					//chars_count++;
				}
			if (c == rw.BACKSPACE)
			{
				if (input_user.length() > 0)
				{
					input_user += "\b";
					//chars_count--;
				}
				//input_user_tmp = rw.BACKSPACE;
			}
			if (c == rw.DEL_KEY)
			{
				if (input_user.length() > 0/* && right_count > 0*/)
				{
					input_user += rw.DEL_KEY;
					//right_count--;
				}
				//input_user_tmp = "\033[D \033[D";
			}
			if ((int)c == rw.ESC) // ESC like \[ \033 \x1b
			{
				read(0, &c, 1);
				if (c == '[')
				{
					read(0, &c, 1);
					//if (c == 'A') input_user += "UP";
					//if (c == 'B') input_user += "DOWN";
					/*if (c == 'C' && right_count > 0)
					{
						input_user_tmp = "\033[C";
						input_user += "\033[C";
						right_count--;
						chars_count++;
					}
					if (c == 'D' && chars_count > 0)
					{
						input_user_tmp = "\033[D";
						input_user += "\033[D";
						right_count++;
						chars_count--;
					}*/
				}
			}
			std::cout << del(input_user) << "\033[1A\n\033[" << del(input_user).length() << "D";
		}
	}
}
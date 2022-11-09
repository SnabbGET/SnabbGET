/**
 * @file cli.cpp
 * @author LAPCoder
 * @brief All CLI shapes (lists, ...)
 * @version 0.1.0
 * 
 * @copyright MIT License
 * 
 */


#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <unistd.h>
#ifdef __linux__
	#include <termios.h>
#endif
#include <functional>
#include <vector>
#include <iterator>
#include <sstream>

/* ┌┬┐╭─╮ ╷
 * ├┼┤│ │╶┼╴
 * └┴┘╰─╯ ╵
 */

std::string operator*(std::string str, int n)
{
	std::ostringstream os;
    for(int i = 0; i < n; i++)
        os << str;
    return os.str();
}

void SnabbGET::CLI::list(int posX, int posY, std::vector<std::string> txt)
{
	std::cout << "\0337\033[" << posY << ";" << posX << "H╭"
		<< std::string("─")*(*std::max_element(txt.begin(), txt.end(),
							[](const auto& a, const auto& b) {
								return a.size() < b.size();
							})).length() // Max size of elements in the vector
		<< "╮\r\n";
	//Result: ╭────╮
	for (unsigned i = 0; i < txt.size(); i++)
		std::cout << "\033[" << posY+i+1 << ";" << posX << "H├" << txt[i]
			<< std::string(" ")*((*std::max_element(txt.begin(), txt.end(),// From here to )
								 [](const auto& a, const auto& b) {        // Add spaces at the end
									 return a.size() < b.size();           // to create a background
								 })).length() -
								 txt[i].length()
								)
			 << "│\r\n";
	//Result: ╭────╮
	//        ├a   │
	//        ├b   │
	std::cout << "\033[" << posY+txt.size()+1 << ";" << posX << "H╰"
		<< std::string("─")*(*std::max_element(txt.begin(), txt.end(),
							[](const auto& a, const auto& b) {
								return a.size() < b.size();
							})).length()
		<< "╯\r\n";
	//Result: ╭────╮
	//        ├aa  │
	//        ├b   │
	//        ╰────╯
	std::cout << "\0338";
}
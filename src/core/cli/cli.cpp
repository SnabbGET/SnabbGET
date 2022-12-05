/**
 * @file cli.cpp
 * @author LAPCoder
 * @brief All CLI shapes (lists, ...)
 * @version 0.2.0
 * 
 * @copyright MIT License
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
#include <algorithm>

/* ┌┬┐╭─╮ ╷
 * ├┼┤│ │╶┼╴
 * └┴┘╰─╯ ╵
 */

std::string operator*(const std::string &str, const int &n)
{
	std::ostringstream os;
	for(int i = 0; i < n; i++)
		os << str;
	return os.str();
}

// Use me to avoid Segment fault!
std::string getElemFromArr(const std::vector<std::vector<std::string>> &arr,
							unsigned c1, unsigned c2)
{
	if (c1 < arr.size())
		if (c2 < arr[c1].size())
			return arr[c1][c2];
	return ""; // Segment fault
}

// Use me to avoid Segment fault!
std::vector<std::string> getElemFromArr(
	const std::vector<std::vector<std::string>> &arr, unsigned c1
)
{
	if (c1 < arr.size())
		return arr[c1];
	return std::vector<std::string>({""}); // Segment fault
}

void SnabbGET::CLI::list(int posX, int posY, const std::vector<std::string> &txt)
{
	std::cout << "\0337\033[" << posY << ";" << posX << "H╭"
		<< std::string("─")*(*std::max_element(txt.begin(), txt.end(),
							[](const auto& a, const auto& b) {
								return a.size() < b.size();
							})).length() // Max size of elements in the vector
		<< "╮";
	//Result: ╭────╮
	for (unsigned i = 0; i < txt.size(); i++)
		std::cout << "\033[" << posY+i+1 << ";" << posX << "H├" << txt[i]
			// Add spaces at the end to create a background
			<< std::string(" ")*((*std::max_element(txt.begin(), txt.end(),
								 [](const auto& a, const auto& b) {
									 return a.size() < b.size();
								 })).length() -
								 txt[i].length()
								)
			 << "│";
	//Result: ╭────╮
	//        ├a   │
	//        ├b   │
	std::cout << "\033[" << posY+txt.size()+1 << ";" << posX << "H╰"
		<< std::string("─")*(*std::max_element(txt.begin(), txt.end(),
							[](const auto& a, const auto& b) {
								return a.size() < b.size();
							})).length()
		<< "╯\0338";
	//Result: ╭────╮
	//        ├aa  │
	//        ├b   │
	//        ╰────╯
}

void SnabbGET::CLI::table(int posX, int posY,
	const std::vector<std::vector<std::string>> &txt, bool with1line = false
)
{
	unsigned line = 0;
	unsigned plusLine = with1line ? 1:0;
	std::cout << "\0337\033[" << posY << ";" << posX << "H╭";
	for (unsigned i = 0; i < txt.size(); i++)
		std::cout << std::string("─")*(*std::max_element(
				txt[i].begin(), txt[i].end(),
				[](const auto& a, const auto& b) {
					return a.size() < b.size();
				}
			)).length() // Max size of elements in the vector
			<< (((long unsigned)i != txt.size()-1) ? "┬":"");
	std::cout << "╮";
	//Result: ╭──┬──┬───╮
	if (with1line)
	{
		std::cout << "\033[" << posY+1+line << ";" << posX << "H";
		for (unsigned i = 0; i < txt.size(); i++)
			std::cout << "│" << getElemFromArr(txt, i, line)
				// getElemFromArr is like txt[i][line], without segment fault
				<<(std::string(" ")*((*std::max_element(
					txt[i].begin(), txt[i].end(),
					[](const auto& a, const auto& b) {
						return a.size() < b.size();
					})).length() -
					getElemFromArr(txt, i, line).length()
				));
		line++;
		std::cout << "│\033[" << posY+1+line << ";" << posX << "H├";
		for (unsigned i = 0; i < txt.size(); i++)
			std::cout << std::string("─")*(*std::max_element(
					txt[i].begin(), txt[i].end(),
					[](const auto& a, const auto& b) {
						return a.size() < b.size();
					})).length() // Max size of elements in the vector
				<< (((long unsigned)i != txt.size()-1) ? "┼":"");
		std::cout << "┤";
	}

	for (; (long unsigned)line < (*std::max_element(txt.begin(), txt.end(),
									[](const auto& a, const auto& b) {
										return a.size() < b.size();
									})).size();
			line++
		)
	{
		std::cout << "\033[" << posY+line+1+plusLine << ";" << posX << "H";
		for (unsigned i = 0; i < txt.size(); i++)
			std::cout << (i != 0 ? "┼":"├") << getElemFromArr(txt, i, line)
			// getElemFromArr is like txt[i][line], without segment fault
				<< std::string(" ")*((*std::max_element(
						txt[i].begin(), txt[i].end(),
						[](const auto& a, const auto& b) {
							return a.size() < b.size();
						}
					)).length() -
					getElemFromArr(txt, i, line).length());
		std::cout << "┤";
	}
	//Result: ╭──┬──┬───╮
	//        ├a ┼  ┼grh┤
	//        ├  ┼1,┼grh┤
	//        ├bc┼  ┼grh┤
	std::cout << "\033[" << posY+line+++1+plusLine << ";" << posX << "H╰";
		// +++ work in C/C++. I created the c+++ !
	for (unsigned i = 0; i < txt.size(); i++)
		std::cout << std::string("─")*(*std::max_element(
				txt[i].begin(), txt[i].end(),
				[](const auto& a, const auto& b) {
					return a.size() < b.size();
				})).length() // Max size of elements in the vector
			<< (((long unsigned)i != txt.size()-1) ? "┴":"");
	std::cout << "╯\0338";
	//Result: ╭──┬──┬───╮
	//        ├a ┼  ┼grh┤
	//        ├  ┼1,┼grh┤
	//        ├bc┼  ┼grh┤
	//        ╰──┴──┴───╯
}

void SnabbGET::CLI::popup(int posX, int posY, const std::string &txt)
{
	std::string tmp, txt2 = replaceAll(txt, "\t", "        ");
	std::stringstream ss(txt);
	std::vector<std::string> words;

	while(getline(ss, tmp, '\n'))
	{
		words.push_back(tmp);
	}

	std::cout << "\0337\033[" << posY << ";" << posX << "H╭"
		<< std::string("─")*(*std::max_element(words.begin(), words.end(),
							[](const auto& a, const auto& b) {
								return a.size() < b.size();
							})).length() // Max size of elements in the vector
		<< "╮";
	//Result: ╭────╮
	for (unsigned i = 0; i < words.size(); i++)
		std::cout << "\033[" << posY+i+1 << ";" << posX << "H│" << words[i]
			// Add spaces at the end to create a background
			<< std::string(" ")*((*std::max_element(words.begin(), words.end(),
								 [](const auto& a, const auto& b) {
									 return a.size() < b.size();
								 })).length() -
								 words[i].length()
								)
			 << "│";
	//Result: ╭────╮
	//        │abcd│
	std::cout << "\033[" << posY+words.size()+1 << ";" << posX << "H╰"
		<< std::string("─")*((*std::max_element(words.begin(), words.end(),
							[](const auto& a, const auto& b) {
								return a.size() < b.size();
							})).length()-1)
		<< "╴⨉\0338";
	//Result: ╭────╮
	//        │abcd│
	//        ╰───╴⨉
}

#include <iostream>
#include <string>
#include <regex>

int main()
{
	std::cout << std::regex_match("hello", std::regex("^([a-z]+)$")) << std::endl;
}

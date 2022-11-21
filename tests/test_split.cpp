#include "../src/core/shell.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
	for (auto a : split("hello, world!", ' ')) std::cout << a << "\n";
	for (auto a : split("hello, world!", 'o')) std::cout << a << "\n";
	for (auto a : split("hello, world!", ',')) std::cout << a << "\n";
	for (auto a : split("hello, world!", '?')) std::cout << a << "\n";
	for (auto a : split("", '?')) std::cout << a << "\n";
	return 0;
}

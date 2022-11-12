#include "../src/core/shell.hpp"
//#include "interface/gui.cpp"

#ifndef std_def
	#include <iostream>
	#include <cstdio>
	#include <string>
	#include <chrono>
	#include <cstdio>
	#include <termios.h>
	#define std_def
	#define print(x, ...) std::cout << x // For a friend :D
#endif

int get_pos(int *y, int *x) {

	char buf[30] = {0};
	int ret, i, pow;
	char ch;
	*y = 0; *x = 0;

	/*struct termios term, restore;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(0, TCSANOW, &term);*/

	write(1, "\033[6n", 4);

	for (i = 0, ch = 0; ch != 'R'; i++)
	{
		ret = read(0, &ch, 1);
		if (!ret) {
			//tcsetattr(0, TCSANOW, &restore);
			fprintf(stderr, "get_pos: Error reading response!\r\n");
			return 1;
		}
		buf[i] = ch;
		//printf("buf[%d]: \t%c \t%d\r\n", i, ch, ch);
	}

	if (i < 2)
	{
		//tcsetattr(0, TCSANOW, &restore);
		printf("i < 2\r\n");
		return 1;
	}

	for (i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
		*x = *x + ( buf[i] - '0' ) * pow;

	for (i--, pow = 1; buf[i] != '['; i--, pow *= 10)
		*y = *y + ( buf[i] - '0' ) * pow;

	//tcsetattr(0, TCSANOW, &restore);
	return 0;
}

int main()
{
	sget::SnabbGET(true);
	sget::rw::Raw_mode(0);
	system("");
	sget::init();
	int posX, posY;
	char a;
	std::vector<std::string> txt({"hello", "i", "", ", ", "want a cake"});
	std::vector<std::vector<std::string>> txt2({
		std::vector<std::string>({"some text", "ttttt"}),
		std::vector<std::string>({"hello", "i", "", ", ", "want a cake"}),
		std::vector<std::string>({"i am", "stilllllllll", "here"}),
		std::vector<std::string>({""}),
		std::vector<std::string>({"haha"})
	});
	std::string txt3("hello i am a string    ");
	get_pos(&posY, &posX);
	posY++;
	//std::cout << "          "<<(posY-txt.size()-3 > 1) ? posY-txt.size()-3:0;
	//sget::CLI::list(posX,(posY-txt.size()-3 > 1) ? posY-txt.size()-3:0, txt);
	//sget::CLI::table(6, 3, txt2, true);
	sget::CLI::popup(5, 3, txt3);
	std::cin >> a;
	sget::read_input("exit");
	sget::rw::pause();
	return EXIT_SUCCESS;
}
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <string>
#include <iostream>


/* Initialize new terminal i/o settings */
static struct termios old, new1;
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new1 = old; /* make new settings same as old settings */
    new1.c_lflag &= ~ICANON; /* disable buffered i/o */
    new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
	new1.c_oflag &= ~(OPOST);
    tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

int main(void)
{
    char c = 0;
    initTermios(0);
	std::cout << "test2: ";

	std::string input_user = "";
	std::string input_user_tmp = "";
	while (1)
	{
		input_user_tmp = "";
		read(0, &c, 1);
		if (c == '\n') break;
		if (((32  <= (int)c) && 
			 (126 >= (int)c)) || 
			((161 <= (int)c) &&
			 (255 >= (int)c)))
			{
				input_user += c;
				input_user_tmp = c;
			}
		if ((int)c == 27) // ESC like \[ \033 \x1b
		{
			read(0, &c, 1);
			if (c == '[')
			{
				read(0, &c, 1);
				if (c == 'A') input_user += "UP";
				if (c == 'B') input_user += "DOWN";
				if (c == 'C') input_user += "RIGHT";
				if (c == 'D') input_user += "LEFT";
			}
		}
		std::cout << input_user_tmp << /*"(" << (int)c << ")" << */"\033[1A\n";
	}
	resetTermios();
	std::cout << std::endl;
	return 0;
}
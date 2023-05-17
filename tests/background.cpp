#include <cstdio>
#include <fstream>
#include <string>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define VC_EXTRALEAN
	#include <Windows.h>
#elif defined(__linux__)
	#include <sys/ioctl.h>
#else
	exit(-1);
#endif

void getTermSize(int &w, int &h)
{ // Specials thanks to @ProjectPhysX (stackoverflow) for saving me!
	#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		w = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
		h = (int)(csbi.srWindow.Bottom-csbi.srWindow.Tpop+1);
	#elif defined(__linux__)
		struct winsize s;
		ioctl(fileno(stdout), TIOCGWINSZ, &s);
		w = (int)(s.ws_col);
		h = (int)(s.ws_row);
	#endif
}

int main()
{
	std::ifstream in("assets/img1_95C.txt", std::ios_base::in);
	std::string f, tmp;
	//int w, h, i = 1;
	//getTermSize(w, h);
	while (in.good()/* && h > i*/)
	{
		//i++;
		std::getline(in, tmp);
		f += tmp;
	}
	const char *f2 = f.c_str();
	/*while (1) */printf("\033[3J%s\033[H\033[0m\033[50A\n", f2);
	//for (int i = 0;i<50;i++) printf("\033M");
}

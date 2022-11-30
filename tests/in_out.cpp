#include <iostream>
#include <string>
#include <functional>
#include <cstdio>

namespace ioSget
{
	class newIo
	{
		public:
			newIo() {}
			int (*outFunct)(const char *, ...) = &std::printf;
			newIo(int (f)(const char *, ...)) {outFunct = f;}
			~newIo() {}
	};

	char *endl = "\r\n";

	typedef std::basic_ostream<char, std::char_traits<char>> stdCoutTpe;
    // this is the function signature of std::endl
    typedef stdCoutTpe& (*stdEndl)(stdCoutTpe&);

	template<typename T>
	inline newIo &operator<<(newIo &exp, T &arg)
	{
		exp.outFunct(arg);
		return exp;
	}
	inline newIo &operator<<(newIo &exp, stdEndl &arg)
	{
		exp.outFunct(endl);
		return exp;
	}
}

ioSget::newIo tstIo;

auto outFunct = std::printf;
// IN/OUT
auto in = &std::cin;
auto out = &tstIo;//&std::cout;

int main()
{
	*out << "hello" << std::endl;
	return 0;
}

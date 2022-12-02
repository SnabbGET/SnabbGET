#include <iostream>
#include <string>
#include <functional>
#include <cstdio>

namespace SnabbGET::io
{
	class newIo
	{
		public:
			// Default constructor
			newIo() {}
			// Output function
			int (*outFunct)(const char *, ...) = &std::printf;
			int (* inFunct)(const char *, ...) = &std::scanf;
			// Constructor with the funtion in param
			newIo(int (o)(const char *, ...),
				  int (i)(const char *, ...)) { outFunct = o; inFunct = i; }
			// Destructor
			~newIo() {}
	};

	std::string endl = "\r\n";

	typedef std::basic_ostream<char, std::char_traits<char>> stdCoutTpe;
    // this is the function signature of std::endl
    typedef stdCoutTpe& (*stdEndl)(stdCoutTpe&);

	template<class T> inline newIo &operator<<(newIo &exp, T &arg)
	{
		exp.outFunct(arg);
		return exp;
	}
	inline newIo &operator<<(newIo &exp, stdEndl arg) // std::endl is a pointer
	{
		exp.outFunct(endl.c_str());
		return exp;
	}
	inline newIo &operator<<(newIo &exp, std::string &arg)
	{
		exp.outFunct(arg.c_str());
		return exp;
	}

	template<class T> inline newIo &operator>>(newIo &exp, T &arg)
	{
		std::string r = "%c";
			 if (typeid(T) == typeid(int)) r = "%d";
		else if (typeid(T) == typeid(char)) r = "%c";
		else if (typeid(T) == typeid(signed char)) r = "%c";
		else if (typeid(T) == typeid(unsigned char)) r = "%c";
		else if (typeid(T) == typeid(float)) r = "%f";
		else if (typeid(T) == typeid(double)) r = "%lf";
		else if (typeid(T) == typeid(long double)) r = "%Lf";
		else if (typeid(T) == typeid(short)) r = "%hd";
		else if (typeid(T) == typeid(unsigned)) r = "%u";
		else if (typeid(T) == typeid(long)) r = "%li";
		else if (typeid(T) == typeid(long long)) r = "%lli";
		else if (typeid(T) == typeid(unsigned long)) r = "%lu";
		else if (typeid(T) == typeid(unsigned long long)) r = "%llu";
		exp.inFunct(r.c_str(), &arg);
		return exp;
	}
	inline newIo &operator>>(newIo &exp, std::string &arg)
	{
		exp.inFunct("%s", arg.c_str());
		return exp;
	}
}

SnabbGET::io::newIo tstIo;
// IN/OUT
auto in = &tstIo;//&std::cin;
auto out = &tstIo;//&std::cout;

int main()
{
	std::string txt;
	*in >> txt;
	*out << txt << "hello" << std::endl;
	return 0;
}

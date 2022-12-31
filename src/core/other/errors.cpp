#include <cstdio>
#include <stdexcept>


/**
 * @brief Handle all SnabbGET s errors
 * 
 */
namespace SnabbGET::err
{
	enum CODE {
		OK				= 0x00000,
		UNKNOW			= 0x00001,
		// BAD section  =   xx1xx
		BAD_INPUT		= 0x00100,
		BAD_VERSION		= 0x00101,
		// Files section=   xx2xx
		ERR_OPEN_FILE	= 0x00200,
		ERR_CREATE_FILE	= 0x00201,
		ERR_DELETE_FILE	= 0x00202,
		// Vars section =   xx3xx
		VAR_OUT_OF_RANGE= 0x00300,
		// PATH var sect=   xx4xx
		GET_PATH_USR	= 0x00400,
		GET_PATH_CMPUT	= 0x00401,
		GET_PATH_PWD	= 0x00402,
		// Fatal
		FATAL			= 0xfffff
	};

	#define THROW_ERR(m) __THROW_ERR(m, __FILE__, __LINE__)
	#define THROW_ERR_MSG(m, msg) __THROW_ERR(m, __FILE__, __LINE__, msg)
	#define __SM(msg, var)\
		do {\
			(var) = (char*)(msg);\
		} while (0);

	void __THROW_ERR(
		CODE e,
		const char *file,
		const int line,
		char *msg = (char*)"\033[1D"
	)
	{
		char *m = (char*)"Error";
		switch (e)
		{
			case OK:
				break;
			case BAD_INPUT:
				__SM("ERROR: Bad input", m); break;
			case BAD_VERSION:
				__SM("ERROR: Bad C++ version: use C++17 or more", m); break;
			case ERR_OPEN_FILE:
				__SM("ERROR: Open a file", m); break;
			case ERR_CREATE_FILE:
				__SM("ERROR: Create a file", m); break;
			case ERR_DELETE_FILE:
				__SM("ERROR: Delete a file", m); break;
			case VAR_OUT_OF_RANGE:
				__SM("ERROR: Out of range", m); break;
			case GET_PATH_USR:
				__SM("ERROR: Can't get username", m); break;
			case GET_PATH_CMPUT:
				__SM("ERROR: Can't get computer name", m); break;
			case GET_PATH_PWD:
				__SM("ERROR: Can't get PWD", m); break;
			default:
				__SM("Unknown error", m); break;
		}
		printf("%s; %s File %s line %d\n", m, msg, file, line);
		addToSCREEN(std::string(m) + "; " + msg + " File " + file + " line "
					+ std::to_string(line));
		if (e == FATAL)
			throw;
	}
}

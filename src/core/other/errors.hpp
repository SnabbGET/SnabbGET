#include <cstdio>
#include <stdexcept>


#ifndef SNABBGET_ERR
#define SNABBGET_ERR

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
		ERR_FIND_FILE	= 0x00203,
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
	);
}

#endif

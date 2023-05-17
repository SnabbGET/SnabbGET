#include <cstdio>
#include <stdexcept>

#include "errors.hpp"

/**
 * @brief Handle all SnabbGET s errors
 * 
 */
namespace SnabbGET::err
{
	void __THROW_ERR(
		CODE e,
		const char *file,
		const int line,
		char *msg
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
			case ERR_FIND_FILE:
				__SM("ERROR: No such file or directory", m); break;
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

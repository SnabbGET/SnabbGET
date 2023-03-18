#ifndef READLINE_LIBRARY
	#define READLINE_LIBRARY
#endif

#include <iostream>
#include "../include/readline/readline.h"
#include  "../include/readline/history.h"

#ifdef HAVE_LOCALE_H
	#include <locale.h>
#endif

int main(int argc, char **argv)
{
	char *line;
	#ifdef HAVE_SETLOCALE
		setlocale(LC_ALL, "");
	#endif
	while (true)
	{
		line = readline(">hgfreyuefhèegzhn_vhg_erh egroger ");
		if (!line) break;
		if (*line) add_history(line);
		if (strcmp(line, "exit") == 0)
			break;
		/* Do something with the line here */
		free(line);
	}
	return EXIT_SUCCESS;
}

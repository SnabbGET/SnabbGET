#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

//#include "../utils.cpp"

const char *txt = "# Here, you can define YOUR prompt.\n\
# Symbols:\n\
# - $$ : $\n\
# - $u : username\n\
# - $m : machine name\n\
# - $d : current dir\n\
# - $t : current time\n\
# - $D : current date\n\
# - $s : DEBUG mode activated? = \"[DEBUG] \"\n\
# - \\033[<color>m is supported\n\
#\n\
# Defalt prompt:\n\
\\033[1m\\033[92m$u@$m\\033[39m:\\033[96m$d\\033[38;5;208m#\\033[31m$t\\033[93m$s\\033[95m |>\n\
# bold  green    @    black :  green    black  #  orange         gold     rose     |>\n\
#           user   machine          dir                      time     debug\n\
# Linux prompt:\n\
# \\033[1m\\033[92m$u@$m\\033[39m:\\033[94m$d $$\n\
# Windows prompt:\n\
# $d>\n\
# Powershell prompt:\n\
# PS $d>\n"; // Sorry for the max line len...

static inline void replaceAll2(std::string &str, const std::string &from,
	const std::string &to
)
{
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
		// Handles case where 'to' is a substring of 'from'
	}
}

std::string SnabbGET::promptSettings()
{
	std::fstream promptFile;
	promptFile.open("./settings/prompt.sget.txt");

	// Check the file
	if (!promptFile.is_open())
	{
		#ifdef DEBUG
			std::cout << "Error opening prompt file!" << std::endl;
		#endif

		// Try to create the file
		promptFile.open("./settings/prompt.sget.txt", std::ios_base::out);
		if (!promptFile.is_open())
		{
			#ifdef DEBUG
				std::cout << "Error creating prompt file!" << std::endl;
			#endif

			// Use system() to create the file
			system("mkdir ./settings");
			system("echo \"\" > ./settings/prompt.sget.txt");

			// Try to open the file again
			promptFile.open("./settings/prompt.sget.txt", std::ios_base::app);
			if (!promptFile.is_open())
			{
				#ifdef DEBUG
					std::cout << "Error opening settings file!" << std::endl;
				#endif
				
				exit(EXIT_FAILURE);
			}
			else
			{
				promptFile << &*txt;
				promptFile.close();
				promptFile.open("../../settings/prompt.sget.txt");
			}
		}
		else
		{
			promptFile << &*txt;
			promptFile.close();
			promptFile.open("../../settings/prompt.sget.txt");
		}
	}
	std::string tmp = "", tmp2, tmp3;
	while (promptFile.good())
	{
		std::getline(promptFile, tmp2);
		tmp += tmp2.rfind("#", 0) != 0 &&
			   tmp2.rfind("\n", 0) != 0 &&
			   tmp2.rfind("\r", 0) != 0 ?
			tmp2:"";
	}
	promptFile.close();

	
	#ifdef DEBUG
		tmp3 = "\033[93m [DEBUG]";
	#endif

//std::string userName = "pi", machineName="raspberrypi", currDir="~/SnabbGET";

	replaceAll2(tmp, "\\033", "\033");
	replaceAll2(tmp, "$$", "œùƒ"); // ;) oeuf == egg
	replaceAll2(tmp, "$u", userName);
	replaceAll2(tmp, "$m", computerName);
	replaceAll2(tmp, "$d", currentDir);
	replaceAll2(tmp, "$s", tmp3);
	replaceAll2(tmp, "$t", gettime());
	replaceAll2(tmp, "$D", getdate());
	replaceAll2(tmp, "œùƒ", "$");
	tmp += "\033[0m ";

	#ifdef __linux__
		tmp += "\033[1A\n";
	#endif
	return tmp;
}
/*
int main()
{
	std::cout << promptSettings() << std::endl;
	return EXIT_SUCCESS;
}
*/
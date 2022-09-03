#include <iostream>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <string>

int main() {
    DIR *dir; struct dirent *diread;
    std::vector<char *> files;

	std::ofstream fileOut;
	remove("./src/core/includesAll.hpp");
	fileOut.open("./src/core/includesAll.hpp", std::ios_base::app);
	fileOut << "#pragma once\n";

    if ((dir = opendir("./src/core/cmd/")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
			if (((std::string)diread->d_name).rfind(".", 0) == std::string::npos)
            	files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return EXIT_FAILURE;
    }

    for (auto file : files)
	{
		std::cout << file << " | ";
		fileOut << "#include \"./cmd/" << file << "\"\n";
	}
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

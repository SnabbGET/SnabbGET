#pragma once

#include <iostream>
#include <string>

std::string getdate();
std::string gettime();
std::string help_params(std::string cmd);

#ifdef FILEENUMERR
    #include "utils.cpp"
#endif
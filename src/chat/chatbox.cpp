// Main file of the chatbox.

/**
 * @file src/main.cpp
 * @brief Main file of the chatbox of the project.
 * @author LAPCoder
 * @version 0.3.0
 * 
 * MIT License
 */

/*----------------------------------------------------------------------------*/
/*---------------- INCLUDES --------------------------------------------------*/
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../../libs/json/json.hpp"

/*----------------------------------------------------------------------------*/
/*---------------- UNSINGS ---------------------------------------------------*/
/*----------------------------------------------------------------------------*/

using json = nlohmann::json;



std::ifstream ask_json("ask.json");
json ask = json::parse(ask_json);

int main()
{
	std::cout << ask["init"] << std::endl << ask["q"] << std::endl;
	std::string response;
	std::cin >> response;

	while (!std::isdigit(response))
	{
		std::cout << ask["bad_r"] << std::endl;
		std::string response;
		std::cin >> response;
		// TODO: handle 'please, 5', or things like '8.'
	}

	std::vector<std::string> argLst;
	unsigned cmdId;

	std::cout << ask["r"][stoi(response)]["q"] << std::endl;
	std::string response;
	std::cin >> response;
	if (ask["r"][stoi(response)]["stack+"][0] != NULL)
		cmdId = ask["r"][stoi(response)]["stack+"][0];
	for (auto i : ask["r"][stoi(response)]["stack+"][1])
	{
		if (i == null)
			i = response;
		argLst.emplace_back(i);
	}

	runCmd();
}


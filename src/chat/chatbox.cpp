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
#include <cassert>
#define JSON_HAS_CPP_17 1
#include "../../include/json/json.hpp"
#include "../core/shell.hpp"
#include "../core/utils.hpp"

/*----------------------------------------------------------------------------*/
/*---------------- USINGS ----------------------------------------------------*/
/*----------------------------------------------------------------------------*/

using json = nlohmann::json;

/*----------------------------------------------------------------------------*/
/*---------------- VARIABLES -------------------------------------------------*/
/*----------------------------------------------------------------------------*/

const json ask = json::parse(std::ifstream("ask.json"), nullptr, true, true);
int cmd = -1;

/*---------------- Extern ----------------------------------------------------*/
/*
std::vector<
	std::function<
		std::string(std::string[], int&, std::string&)
	>
> sget::CMDS::cmdLst =
	std::vector<std::function<std::string(std::string[], int&, std::string&)>>();
*/

/*----------------------------------------------------------------------------*/
/*---------------- FUNCTIONS -------------------------------------------------*/
/*----------------------------------------------------------------------------*/

bool is_number_better(std::string response)
{
	response.erase(remove_if(response.begin(), response.end(), isspace), response.end());
	try {
		atoi(response.c_str());
		return true;
	} catch (const std::invalid_argument&) {
		return false;
	}
}

// Recursive function
std::pair<std::vector<std::string>, int> next_q(
	std::string response,
	std::vector<std::string> argLst,
	int cmdId,
	json ask_path = ask["r"][cmd])
{
	if (ask_path["q"] != nullptr)
	{
		std::cout << ask_path["q"].template get<std::string>() << std::endl;

		std::cin >> response;
		if (ask_path["stack+"][0] != nullptr)
			cmdId = ask_path["stack+"][0];
		for (auto i : ask_path["stack+"][1])
		{
			if (i == nullptr)
				i = response;
			argLst.emplace_back(i.template get<std::string>());
		}

		if (ask_path["end"] == false)
		{
			auto n = next_q(response, argLst, cmdId, ask_path["r"]);
			argLst = n.first;
			cmdId = n.second;
		}
	}
	return std::make_pair(argLst, cmdId);
}

/*----------------------------------------------------------------------------*/
/*---------------- MAIN ------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

int main()
{
	system("");

	// Init SnabbGET
	sget::SnabbGET();
	sget::rw::Raw_mode(0, false);
	sget::io::io.outFunct = &std::printf;
	sget::io::io.inFunct = &std::scanf;

	std::string response;

	std::cout << ask["init"].template get<std::string>() << std::endl;

	while (cmd != 0)
	{
		// 1st question
		for (auto i : ask["q"])
			std::cout << i.template get<std::string>() << std::endl;

		std::cout << ">>> ";

		response.clear();
		std::cin >> response;

		while (!is_number_better(response))
		{
			std::cout << ask["bad_r"].template get<std::string>() << std::endl << ">>> ";
			response.clear();
			std::cin >> response;
			// TODO: handle 'please, 5', or things like '8.'
		}

		cmd = atoi(response.c_str());
		assert(cmd >= 0);

		response.clear();

		std::vector<std::string> argLst;
		argLst.emplace_back(std::string(sget::CMDS::allCmd[cmd][0]));
		int cmdId = 1;

		auto n = next_q(response, argLst, cmdId);
		argLst = n.first;
		cmdId = n.second;

		std::cout << sget::runCmd(
			cmdId,
			argLst.data(),
			argLst.size(), 
			std::accumulate(
				argLst.begin(),
				argLst.end(),
				std::string{},
				[](std::string &s, const std::string &piece) -> decltype(auto) { return s += piece + ' '; })
		) << std::endl;
	}

	return EXIT_SUCCESS;
}


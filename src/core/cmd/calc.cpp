// Calc command

#include "../shell.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <unistd.h>
#include <algorithm>

//#include "../shell.hpp"

#include "../../../include/exprtk/exprtk.hpp"

/**
 * @brief Calc command
 * 
 * @param cmd The user command in array
 * @param cmdLen [NOT USED]
 * @param input_user The user input
 * @return [std::string] Command result
 */
std::string SnabbGET::CMDS::_calc_(std::string cmd[],int,std::string input_user)
{
	if (input_user.length() < cmd[0].length()+1)
		return "0";
	
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>   expression_t;
	typedef exprtk::parser<double>       parser_t;

	symbol_table_t symbol_table;
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(input_user.substr(cmd[0].length()+1), expression);

	return std::to_string(expression.value());
}

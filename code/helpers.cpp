#include "helpers.h"
#include <iostream>

//Print a string to the console; if end_line is true, print a new line at the end
void print(string output, bool end_line)
{
	if(end_line)
		std::cout << output << std::endl;
	else
		std::cout << output;
}

//Get input from the user and store it in the input variable as a string
bool string_input(string &input)
{
	std::getline(std::cin, input);
	return !input.empty();	//Returns true if the input is not empty for iteration purposes
}

//Get input from the user and store it in the input variable as an integer
void int_input(int &input)
{
	string temp;
	std::getline(std::cin, temp);
	input = std::stoi(temp);
}

//Get input from the user and store it in the input variable as a double
void double_input(double &input)
{
	string temp;
	std::getline(std::cin, temp);
	input = std::stod(temp);
}

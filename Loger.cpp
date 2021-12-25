#include<iostream>
#include <fstream>

#include "Loger.h"

bool Loger::write_message_to_file(std::string text)
{
	std::ofstream file;
	file.open("log.txt", std::ios::out | std::ios::app);

	if (file.is_open())
	{
		std::cout << text << std::endl;

		file << text << std::endl;

		file.close();

		return true;
	}
	else
	{
		file << "Error. File log.txt can`t open." << std::endl;
		return false;
	}
}
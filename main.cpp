#include <iostream>
#include <fstream>
#include <chrono>

#include "Loger.h"
#include "Parser_CSV.h"

int main(int argc, char* argv[])
{
	std::cout << "Have " << argc << " arguments:" << std::endl;
	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	Parser_CSV parser_arg(argv[1], argv[2]);

	if (parser_arg.read_line_from_file() == false)
	{
		return -1;
	}

	parser_arg.process_data();

	if (parser_arg.write_to_file() == false)
	{
		return -1;
	}

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

	std::cout << "Parsing time: " << time << " nanoseconds." << std::endl;

	return 0;
}
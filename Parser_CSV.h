#pragma once
#include <iostream>
#include <vector>
#include <map>

class Parser_CSV
{
public:
	Parser_CSV(std::string file_name, std::string out_file_name);
	bool read_line_from_file();
	std::vector<std::string> split_line(std::string str);
	std::string get_month_name(std::string oder_number);
	void process_data();
	bool write_to_file();

private:
	std::vector<std::vector<std::string>> m_lines;
	std::map < std::string, std::map<std::string, std::string>> m_workers;
	std::string m_input_file_name;
	std::string m_output_file_name;
};
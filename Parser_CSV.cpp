#include "Parser_CSV.h"
#include "Loger.h"
#include <fstream>

Parser_CSV::Parser_CSV(std::string file_name, std::string out_file_name)
	: m_input_file_name(file_name), m_output_file_name(out_file_name)
{
}

bool Parser_CSV::read_line_from_file()
{
	std::ifstream file_read;
	file_read.open(m_input_file_name);

	std::string str;

	if (file_read.is_open())
	{
		Loger::write_message_to_file("File data.csv open.");

		while (!file_read.eof())
		{
			std::getline(file_read, str);

			auto words = split_line(str);

			if (!words.empty())
			{
				m_lines.push_back(words);
			}
		}

		file_read.close();
		Loger::write_message_to_file("File data.csv close.");

		return true;
	}
	else
	{
		Loger::write_message_to_file("File data.csv can`t open.");

		return false;
	}
}

std::vector<std::string> Parser_CSV::split_line(std::string str)
{
	char* content;
	const char* separators = ";,:'\n";
	char* token = strtok_s(const_cast<char*>(str.c_str()), separators, &content);

	std::vector<std::string> result;

	while (token != NULL)
	{
		result.push_back(token);
		token = strtok_s(NULL, separators, &content);
	}

	return result;
}

//Separated date into day, month and year
std::string Parser_CSV::get_month_name(std::string oder_number)
{
	std::vector<std::string> month{ "January" , "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	std::string res;

	int m = std::stoi(oder_number.substr(5, 2));
	int d = std::stoi(oder_number.substr(2));

	if (m > 0)
	{
		res = month[m - 1] + " " + oder_number.substr(0, 4);
	}

	return res;
}

void Parser_CSV::process_data()
{
	for (auto& line : m_lines)
	{
		auto& name = line[0];
		auto& date = line[6];
		auto& logged_hours = line[7];

		//First line containing information about data in the table
		if (line[7] == "Logged hours" && line[6] == "Date")
		{
			line[7] = "Total hours";
			line[6] = "Month";
			m_workers[name][date] = logged_hours;
		}
		else
		{
			std::string month = get_month_name(date);

			//Sums up the loggeg hours of each employee for the month
			int sum = 0;
			if (!m_workers[name][month].empty())
			{
				sum = stoi(m_workers[name][month]);
			}

			int value = atoi(logged_hours.c_str());
			sum += value;

			m_workers[name][month] = std::to_string(sum);
		}
	}
}

bool Parser_CSV::write_to_file()
{
	std::ofstream file;
	file.open(m_output_file_name);

	if (file.is_open())
	{
		Loger::write_message_to_file("File out.csv open.");

		// Writting to file information about workers
		for (auto it = m_workers.rbegin(); it != m_workers.rend(); ++it)
		{
			file << it->first << ";";
			for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				file << it2->first << ";" << it2->second << ";";
			}
			file << std::endl;
		}

		file.close();
		Loger::write_message_to_file("File out.csv close.");

		return true;
	}
	else
	{
		Loger::write_message_to_file("File data.csv can`t open.");

		return false;
	}
}
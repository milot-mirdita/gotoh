#pragma once
#include <string>
#include <map>

class sequence_library
{
public:
	sequence_library(std::string file);
	std::string get_sequence(std::string id);

	unsigned int max_length;

protected:
	std::map<std::string, std::string> sequences;
};


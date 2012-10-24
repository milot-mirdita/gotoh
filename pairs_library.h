#pragma once
#include <string>
#include <map>

class pairs_library
{
public:
	pairs_library(std::string file);
	std::map<std::string, std::string> pairs;
};


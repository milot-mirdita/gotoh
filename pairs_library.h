#pragma once
#include <string>
#include <vector>

class pairs_library
{
public:
	pairs_library(std::string file);
	std::vector<std::pair<std::string, std::string>> pairs;
};


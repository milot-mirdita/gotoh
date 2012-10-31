#include "pairs_library.h"
#include <fstream>
#include "util.h"


pairs_library::pairs_library(std::string file) {
	std::ifstream in(file);
	std::string line;
	while(std::getline(in, line)) {
		std::vector<std::string> myvect = split(line, ' ');
		pairs.push_back(std::pair<std::string, std::string>(myvect.at(0), myvect.at(1)));
	}
}

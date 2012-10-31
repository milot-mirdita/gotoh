#include "sequence_library.h"
#include <fstream>
#include "util.h"
#include <algorithm>

sequence_library::sequence_library(std::string file) {
	max_length = 0;
	std::ifstream in(file.c_str());
	std::string line;
	while(std::getline(in, line)) {
        std::vector<std::string> myvect= split(line,':');
		std::string identifier = myvect.at(0);
		std::string sequence = myvect.at(1);
		sequences.insert(std::pair<std::string, std::string>(identifier, sequence));
		max_length = std::max((unsigned int) sequence.length(), max_length);
	}
}

std::string sequence_library::get_sequence(std::string id) {
	return sequences.find(id)->second;
}


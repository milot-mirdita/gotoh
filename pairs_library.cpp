#include "pairs_library.h"
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

pairs_library::pairs_library(std::string file)
{
	std::ifstream in(file);
	std::string line;
	while(std::getline(in, line)) {
		boost::char_separator<char> sep(" ");
		boost::tokenizer<boost::char_separator<char>> tokens(line, sep);
		auto iterator = tokens.begin();
		pairs.insert(iterator++, iterator);
	}
}

#include "secondary_structure_preference.h"
#include <fstream>
#include <sstream>
#include "util.h"
#include "amino_acid_lookup.h"

secondary_structure_preference::secondary_structure_preference(std::string file, float scale_factor) {
	this->scale_factor = scale_factor;
	std::ifstream in(file);
	std::string line;
	int currentType = -1;
	while(std::getline(in, line)) {
		if(currentType >= 0 && currentType < 3) {
			std::stringstream sstream;
			std::string three_letter_code;
			float preference;

			sstream << line;
			sstream >> three_letter_code;
			sstream >> preference;

			int one_letter_code = (int) amino_acid_lookup::find_one_letter_code(three_letter_code) - 65;
			scores[currentType][one_letter_code] = (int) (preference * scale_factor);
		}

		if(line.find("ALPHA") != std::string::npos) {
			currentType = 0;
		}
		if(line.find("BETA") != std::string::npos) {
			currentType = 1;

		}
		if(line.find("OTHER") != std::string::npos) {
			currentType = 2;
		}
	}
}

secondary_structure_preference::~secondary_structure_preference(void)
{
}
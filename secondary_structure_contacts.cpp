#include "secondary_structure_contacts.h"
#include <string>
#include <sstream>
#include <fstream>

#include "amino_acid_lookup.h"

void secondary_structure_contacts::parse_file(std::string file) {
	std::ifstream in(file);
	std::string line;
	int current_line = 0;
	std::getline(in, line);
	while(std::getline(in, line)) {
		std::stringstream sstream;

		std::string three_letter_code;
		std::string secondary_structure;
		unsigned char ss_struct;
		int global_contacts;
		int local_contacts;

		sstream << line;
		sstream >> three_letter_code;
		sstream >> secondary_structure;
		sstream >> global_contacts;
		sstream >> local_contacts;

		if(secondary_structure.at(0) == 'a') {
			ss_struct = 0;
		} else if (secondary_structure.at(0)  == 'b') {
			ss_struct = 1;
		} else {
			ss_struct = 2;
		}
		//unsigned char one_letter_code = (unsigned char) amino_acid_lookup::find_one_letter_code(three_letter_code) - 65;
			
		entries.secondary_structure[current_line]	= ss_struct;
		entries.global_contacts[current_line]		= global_contacts;
		entries.local_contacts[current_line]		= local_contacts;

		current_line++;
	}
	entries.length = current_line;
}

secondary_structure_contacts::secondary_structure_contacts( int max_length )  : max_length(max_length) {
	//entries.residue = new unsigned char[max_length];
	entries.secondary_structure = new unsigned char[max_length];
	entries.global_contacts = new int[max_length];
	entries.local_contacts = new int[max_length];
}

secondary_structure_contacts::~secondary_structure_contacts(void) {
	delete entries.local_contacts;
	delete entries.global_contacts;
	delete entries.secondary_structure;
	//delete entries.residue;
}

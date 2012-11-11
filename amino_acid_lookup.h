#pragma once
#include <map>
#include <string>
#include <memory>

class amino_acid_lookup
{
public:
	std::map<std::string, char> three_to_one;
	std::map<char, std::string> one_to_three;

	static amino_acid_lookup& get_instance()
	{
		static amino_acid_lookup instance;
		return instance;
	};

	static char find_one_letter_code(std::string three_letter_code) {
		amino_acid_lookup& lookup = amino_acid_lookup::get_instance();
		std::map<std::string, char>::iterator element = lookup.three_to_one.find(three_letter_code);
		if(element == lookup.three_to_one.end())
			return 'X';
		return element->second;
	}

	static std::string find_thee_letter_code(char one_letter_code) {
		amino_acid_lookup& lookup = amino_acid_lookup::get_instance();
		std::map<char, std::string>::iterator element = lookup.one_to_three.find(one_letter_code);
		if(element == lookup.one_to_three.end())
			return "UNK";
		return element->second;
	}
private:
	amino_acid_lookup(void);
	amino_acid_lookup(amino_acid_lookup const&);
	void operator=(amino_acid_lookup const&);
};


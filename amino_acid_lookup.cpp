#include "amino_acid_lookup.h"

amino_acid_lookup::amino_acid_lookup(void)
{
	three_to_one.insert(std::pair<std::string, char>("ALA", 'A'));
	three_to_one.insert(std::pair<std::string, char>("ASP", 'D'));
	three_to_one.insert(std::pair<std::string, char>("ASN", 'N'));
	three_to_one.insert(std::pair<std::string, char>("ASX", 'B'));
	three_to_one.insert(std::pair<std::string, char>("ARG", 'R'));
	three_to_one.insert(std::pair<std::string, char>("CYS", 'C'));
	three_to_one.insert(std::pair<std::string, char>("GLU", 'E'));
	three_to_one.insert(std::pair<std::string, char>("GLN", 'Q'));
	three_to_one.insert(std::pair<std::string, char>("GLY", 'G'));
	three_to_one.insert(std::pair<std::string, char>("GLX", 'Z'));
	three_to_one.insert(std::pair<std::string, char>("HIS", 'H'));
	three_to_one.insert(std::pair<std::string, char>("ILE", 'I'));
	three_to_one.insert(std::pair<std::string, char>("LYS", 'K'));
	three_to_one.insert(std::pair<std::string, char>("LEU", 'L'));
	three_to_one.insert(std::pair<std::string, char>("MET", 'M'));
	three_to_one.insert(std::pair<std::string, char>("PHE", 'F'));
	three_to_one.insert(std::pair<std::string, char>("PRO", 'P'));
	three_to_one.insert(std::pair<std::string, char>("SER", 'S'));
	three_to_one.insert(std::pair<std::string, char>("THR", 'T'));
	three_to_one.insert(std::pair<std::string, char>("TRP", 'W'));
	three_to_one.insert(std::pair<std::string, char>("TYR", 'Y'));
	three_to_one.insert(std::pair<std::string, char>("VAL", 'V'));
	three_to_one.insert(std::pair<std::string, char>("UNK", 'X'));

	one_to_three.insert(std::pair<char, std::string>('A', "ALA"));
	one_to_three.insert(std::pair<char, std::string>('D', "ASP"));
	one_to_three.insert(std::pair<char, std::string>('N', "ASN"));
	one_to_three.insert(std::pair<char, std::string>('B', "ASX"));
	one_to_three.insert(std::pair<char, std::string>('R', "ARG"));
	one_to_three.insert(std::pair<char, std::string>('C', "CYS"));
	one_to_three.insert(std::pair<char, std::string>('E', "GLU"));
	one_to_three.insert(std::pair<char, std::string>('Q', "GLN"));
	one_to_three.insert(std::pair<char, std::string>('G', "GLY"));
	one_to_three.insert(std::pair<char, std::string>('Z', "GLX"));
	one_to_three.insert(std::pair<char, std::string>('H', "HIS"));
	one_to_three.insert(std::pair<char, std::string>('I', "ILE"));
	one_to_three.insert(std::pair<char, std::string>('K', "LYS"));
	one_to_three.insert(std::pair<char, std::string>('L', "LEU"));
	one_to_three.insert(std::pair<char, std::string>('M', "MET"));
	one_to_three.insert(std::pair<char, std::string>('F', "PHE"));
	one_to_three.insert(std::pair<char, std::string>('P', "PRO"));
	one_to_three.insert(std::pair<char, std::string>('S', "SER"));
	one_to_three.insert(std::pair<char, std::string>('T', "THR"));
	one_to_three.insert(std::pair<char, std::string>('W', "TRP"));
	one_to_three.insert(std::pair<char, std::string>('Y', "TYR"));
	one_to_three.insert(std::pair<char, std::string>('V', "VAL"));
	one_to_three.insert(std::pair<char, std::string>('X', "UNK"));
}

amino_acid_lookup::amino_acid_lookup( amino_acid_lookup const& ) {}

void amino_acid_lookup::operator=( amino_acid_lookup const& ) {}

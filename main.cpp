#include <iostream>
#include <map>
#include <string>
#include <boost/foreach.hpp>

#include "substitution_matrix.h"
#include "gotoh.h"
#include "sequence_library.h"
#include "pairs_library.h"


int main(int argc, char* argv[])
{
	sequence_library sequences("C:\\Users\\Milot\\Desktop\\assignment1\\domains.seqlib");
	pairs_library pairs("C:\\Users\\Milot\\Desktop\\assignment1\\cathscop.inpairs");
	substitution_matrix matrix("C:\\Users\\Milot\\Documents\\Visual Studio 2010\\Projects\\gotoh\\Debug\\matrices\\dayhoff.mat");
	
	//gotoh run("MKLFYKPGACSLASHITLRESGKDFTLVSVDLMKKRLENGDDYFAVNPKGQVPALLLDDGTLLTEGVAIMQYLADSVPDRQLPEVQDALSAEGL", "KEAQSLLEQIRDIDGDFEFETYYSLSCHNCPDVVQALNLMAVLNPRIKHTAIDGGTFQNEITERNVMGVPAVFVNGKEFGQGRMTLTEIVAKVD", &matrix);

	int i = 0;
	BOOST_FOREACH(auto pair, pairs.pairs) {
		std::string sequence1 = sequences.get_sequence(pair.first);
		std::string sequence2 = sequences.get_sequence(pair.second);
		gotoh run(sequence1, sequence2, &matrix);
		if(i % 10 == 0) {
			std::cout << ".";
		}
		i++;
	}
	return 0;
}

#include <iostream>
#include <map>
#include <string>
#include <boost/foreach.hpp>

#include <tclap/CmdLine.h>

#include "substitution_matrix.h"
#include "gotoh.h"
#include "sequence_library.h"
#include "pairs_library.h"


int main(int argc, char* argv[])
{
	TCLAP::CmdLine cmd("this is a message", '=', "0.01" );
	TCLAP::ValueArg<float> go("go", "gap-open", "gap open score (Standard -12)", true, -12.0f, "float", cmd);
	TCLAP::ValueArg<float> go("ge", "gap-extend", "gap extend score (Standard -1)", true, -1.0f, "float", cmd);

	TCLAP::SwitchArg check("pa", "printali","gibt auch jedes Alignment aus", cmd, false);
	TCLAP::SwitchArg check("c", "check","ueberprueft die berechneten Scores anhand des Alignments", cmd, false);
	
	std::vector<std::string> alignment_modes;
	alignment_modes.push_back("local");
	alignment_modes.push_back("global");
	alignment_modes.push_back("freeshift");
	TCLAP::ValuesConstraint<std::string> alignment_mode_constraint( alignment_modes );
	TCLAP::ValueArg<std::string> modes("mo", "mode", "alignment type", true, "global", &alignment_mode_constraint, cmd);

	std::vector<std::string> output_types;
	output_types.push_back("html");
	output_types.push_back("txt");
	TCLAP::ValuesConstraint<std::string> output_type_constraint( output_types );
	TCLAP::ValueArg<std::string> modes("pm", "printmatrices", "eines aus txt|html, gibt auch die Gotoh-Matrizen aus, entweder als tab separiert oder html", true, "txt", &output_type_constraint, cmd);


	cmd.parse( argc, argv );

	sequence_library sequences("C:\\Users\\Milot\\Desktop\\assignment1\\domains.seqlib");
	pairs_library pairs("C:\\Users\\Milot\\Desktop\\assignment1\\cathscop.inpairs");
	substitution_matrix matrix("C:\\Users\\Milot\\Documents\\Visual Studio 2010\\Projects\\gotoh\\Debug\\matrices\\dayhoff.mat");

	int i = 0;
	BOOST_FOREACH(auto pair, pairs.pairs) {
		std::string sequence1 = sequences.get_sequence(pair.first);
		std::string sequence2 = sequences.get_sequence(pair.second);
		gotoh run(sequence1, sequence2, &matrix);
		if(i % 100 == 0) {
			std::cout << ".";
		}
		i++;
	}
	return 0;
}

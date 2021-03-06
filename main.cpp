#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#define TCLAP_FLAGSTARTSTRING "-"
#define TCLAP_NAMESTARTSTRING "-"
#include <tclap/CmdLine.h>

#include "substitution_matrix.h"
#include "gotoh.h"
#include "sequence_library.h"
#include "pairs_library.h"

int main(int argc, char* argv[]) {
	TCLAP::CmdLine cmd("Gotoh", ' ', "0.01" );
	TCLAP::ValueArg<float> gap_open_arg("o", "gap-open", "gap open score (Standard -12)", false, -12.0f, "int", cmd);
	TCLAP::ValueArg<float> gap_extend_arg("e", "gap-extend", "gap extend score (Standard -1)", false, -1.0f, "int", cmd);

	TCLAP::SwitchArg print_alignment_arg("a", "printali","gibt auch jedes Alignment aus", cmd, false);
	TCLAP::SwitchArg check_arg("c", "check","ueberprueft die berechneten Scores anhand des Alignments", cmd, false);

	std::vector<std::string> alignment_modes;
	alignment_modes.push_back("local");
	alignment_modes.push_back("global");
	alignment_modes.push_back("freeshift");
	TCLAP::ValuesConstraint<std::string> alignment_mode_constraint( alignment_modes );
	TCLAP::ValueArg<std::string> alignment_modes_arg("d", "mode", "alignment type", false, "global", &alignment_mode_constraint, cmd);

	std::vector<std::string> output_types;
	output_types.push_back("none");
	output_types.push_back("html");
	output_types.push_back("txt");
	TCLAP::ValuesConstraint<std::string> output_type_constraint( output_types );
	TCLAP::ValueArg<std::string> print_matrices_arg("t", "printmatrices", "eines aus txt|html, gibt auch die Gotoh-Matrizen aus, entweder als tab separiert oder html", false, "none", &output_type_constraint, cmd);

	TCLAP::ValueArg<std::string> substitution_matrix_arg("m", "matrix", "matrix", false, "matrices/dayhoff.mat", "string", cmd);
	TCLAP::ValueArg<std::string> sequence_library_arg("s", "seqlib", "Name to print", true, "", "string", cmd);
	TCLAP::ValueArg<std::string> pairs_libarary_arg("p", "pairs","Name to print", true, "", "string", cmd);
	cmd.parse( argc, argv );

	float scale_factor = 10.0f;
	int gap_open = (int) (gap_open_arg.getValue() * scale_factor);
	int gap_extend = (int) (gap_extend_arg.getValue() * scale_factor);

	sequence_library sequences(sequence_library_arg.getValue());
 	pairs_library pairs(pairs_libarary_arg.getValue());
 	substitution_matrix matrix(substitution_matrix_arg.getValue(), scale_factor);
 
	gotoh runner(sequences.max_length, gap_open, gap_extend, &matrix, alignment_modes_arg.getValue());
 	for(auto i = pairs.pairs.begin(); i != pairs.pairs.end(); i++) {
 		std::string sequence1 = sequences.get_sequence(i->first);
 		std::string sequence2 = sequences.get_sequence(i->second);
		runner.run(sequence1, sequence2);

		std::cout.precision(3);
		if(print_alignment_arg.getValue() == false) {
			float score = runner.get_score();
			std::cout << i->first << " " << i->second << " " << std::fixed << score << std::endl;
		} else {
			auto alignment = runner.get_alignment();
			std::cout << "> " << i->first << " " << i->second << " " << std::fixed << runner.get_score() << std::endl;
			std::cout << i->first << ": " << alignment.first << std::endl;
			std::cout << i->second << ": " << alignment.second << std::endl;
			if(check_arg.getValue()) {
				float check_score = runner.get_score(alignment,  alignment_modes_arg.getValue());
				if(check_score != runner.get_score()) {
					std::cout << "check: false, score: " << std::fixed << check_score << std::endl;
				} else {
					std::cout << "check: true, score: " << std::fixed << check_score << std::endl;
				}
			}
		}

		if(print_matrices_arg.getValue().find("none") == std::string::npos) {
			runner.print_matrices(print_matrices_arg.getValue());
		}
	}

	return 0;
}
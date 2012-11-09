#include "gotoh.h"
#include "a_matrix_freeshift.h"
#include "a_matrix_local.h"
#include <cfloat>

gotoh::gotoh(unsigned int size, int gap_open, int gap_extend, substitution_matrix* matrix, std::string alignment_type)
	: size(size), gap_open(gap_open), gap_extend(gap_extend), matrix(matrix), alignment_type(alignment_type) {	
	dm = new d_matrix(size, matrix, gap_open, gap_extend);
	im = new i_matrix(size, matrix, gap_open, gap_extend);

	if(alignment_type.find("local") != std::string::npos) {
		am = new a_matrix_local(size, matrix, gap_open, gap_extend, dm, im);
	} else if (alignment_type.find("freeshift") != std::string::npos) {
		am = new a_matrix_freeshift(size, matrix, gap_open, gap_extend, dm, im);
	} else if (alignment_type.find("global") != std::string::npos) {
		am = new a_matrix(size, matrix, gap_open, gap_extend, dm, im);
	}

	dm->init();
	im->init();
	am->init();

	dm->set_a_matrix(am);
	im->set_a_matrix(am);
}

gotoh::~gotoh() {
	delete am;
	delete im;
	delete dm;
}

void gotoh::run(std::string sequence1, std::string sequence2) {
	dm->set_sequences(sequence1, sequence2);
	im->set_sequences(sequence1, sequence2);
	am->set_sequences(sequence1, sequence2);

	for(int i = 0; i < am->rows; i++) {
		for(int j = 0; j < am->cols; j++) {
			if(j != 0)
				dm->fill_in(i, j);
			if(i != 0)
				im->fill_in(i, j);
			if(i != 0 && j != 0)
				am->fill_in(i, j);
		}
	}
}

float gotoh::get_score() {
	int score_cell = am->get_traceback_start();
	return (float) am->cells[score_cell] / matrix->scale_factor;
}

float gotoh::get_score(std::pair<std::string, std::string> alignment) {
	std::string sequence1 = alignment.first;
	std::string sequence2 = alignment.second;
	if(sequence1.length() != sequence2.length())
		return -FLT_MAX;
	
	int score = 0;
	bool is_gap_open = false;
	for(unsigned int i = 0; i < sequence1.length(); i++) {
		if(sequence1.at(i) == '-' || sequence2.at(i) == '-') {
			if(is_gap_open) {
				score += gap_extend;
			} else {
				score += gap_open;
				is_gap_open = true;
			}
			continue;
		}
		score += matrix->get_score(sequence1.at(i), sequence2.at(i));
		is_gap_open = false;
	}
	
	return ((float)score) / ((float) matrix->scale_factor);
}

std::pair<std::string, std::string>  gotoh::get_alignment() {
	return am->get_traceback();
}

void gotoh::print_matrices(std::string type = "txt") {
	if (type.find("txt") != std::string::npos) {
		dm->print();
		im->print();
		am->print();
	} else if (type.find("html") != std::string::npos) {
		dm->print_html();
		im->print_html();
		am->print_html();
	}
}

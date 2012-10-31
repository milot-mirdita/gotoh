#include "gotoh.h"

gotoh::gotoh(unsigned int size, int gap_open, int gap_extend, substitution_matrix* matrix)
	: size(size), gap_open(gap_open), gap_extend(gap_extend), matrix(matrix)
{	
	dm = new d_matrix(size, matrix, gap_open, gap_extend);
	im = new i_matrix(size, matrix, gap_open, gap_extend);
	am = new a_matrix(size, matrix, gap_open, gap_extend, dm, im);

	dm->init();
	im->init();
	am->init();

	dm->set_a_matrix(am);
	im->set_a_matrix(am);
}

gotoh::~gotoh()
{
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

	//dm->print();
	//im->print();
	//am->print();

	std::pair<std::string, std::string> alignment = am->get_traceback();
}
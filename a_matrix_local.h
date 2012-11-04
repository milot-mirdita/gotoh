#pragma once
#include "a_matrix.h"

class a_matrix_local : public a_matrix
{
public:
	a_matrix_local(unsigned int size, substitution_matrix* substitution,
		int gap_open, int gap_extend, matrix* d_matrix, matrix* i_matrix) 
		: a_matrix(size, substitution, gap_open, gap_extend, d_matrix, i_matrix) {
			max_local_score = min_score;
	};

protected:
	virtual void set_sequences(std::string sequence1, std::string sequence2);

	virtual int get_initial_score(int row, int col);
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);

	virtual bool is_traceback_done(cell* current);
	virtual cell* get_traceback_start();

	cell* max_local;
	int max_local_score;
};


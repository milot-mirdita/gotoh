#pragma once
#include "a_matrix.h"
#include <climits>

class a_matrix_local : public a_matrix
{
public:
	a_matrix_local(unsigned int size, substitution_matrix* substitution,
		int gap_open, int gap_extend, matrix* d_matrix, matrix* i_matrix) 
		: a_matrix(size, substitution, gap_open, gap_extend, d_matrix, i_matrix) {
			max_local_score = INT_MIN;
	};

protected:
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);

	virtual bool is_traceback_done(cell* current);
	virtual cell* get_traceback_start();

	cell* max_local;
	int max_local_score;
};


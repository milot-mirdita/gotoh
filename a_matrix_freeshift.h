#pragma once
#include "a_matrix.h"

class a_matrix_freeshift : public a_matrix
{
public:
	a_matrix_freeshift(unsigned int size, substitution_matrix* substitution,
		int gap_open, int gap_extend, matrix* d_matrix, matrix* i_matrix)  
		: a_matrix(size, substitution, gap_open, gap_extend, d_matrix, i_matrix) {};

protected:
	virtual int get_initial_score(int row, int col);
	virtual int get_traceback_start();
	virtual bool is_traceback_done(int current);
};


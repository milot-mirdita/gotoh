#pragma once
#include "matrix.h"

class a_matrix : public matrix
{
public:
	a_matrix(unsigned int size, substitution_matrix* substitution,
		int gap_open, int gap_extend, matrix* d_matrix, matrix* i_matrix) 
		: matrix(size, substitution, gap_open, gap_extend), d_matrix(d_matrix), i_matrix(i_matrix) {};

	virtual void fill_in(int row, int col);

	virtual std::pair<std::string, std::string> get_traceback();
	virtual int get_traceback_start();

	friend class d_matrix;
	friend class i_matrix;

protected:
	int gap_cost(int k);

	virtual int get_initial_score(int row, int col);

	virtual bool is_traceback_done(int current);

	matrix* d_matrix;
	matrix* i_matrix;
};


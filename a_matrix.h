#pragma once
#include "matrix.h"
#include "alignment_type.h"


class a_matrix : public matrix
{
public:
	a_matrix(unsigned int size, substitution_matrix* substitution,
		float gap_open, float gap_extend, matrix* d_matrix, matrix* i_matrix) 
		: matrix(size, substitution, gap_open, gap_extend), d_matrix(d_matrix), i_matrix(i_matrix) {};

	virtual std::pair<std::string, std::string> get_traceback();

	friend class d_matrix;
	friend class i_matrix;

protected:
	float gap_cost(int k);

	virtual float get_initial_score(int row, int col);
	virtual cell* get_initial_pointer(int row, int col);
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);

	virtual bool is_traceback_done(cell* current);
	virtual cell* get_traceback_start();

	matrix* d_matrix;
	matrix* i_matrix;
};


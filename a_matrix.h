#pragma once
#include "matrix.h"

class a_matrix : public matrix
{
private:
	matrix* d_matrix;
	matrix* i_matrix;

public:
	a_matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, 
		float gap_open, float gap_extend, matrix* d_matrix, matrix* i_matrix) 
		: matrix(sequence1, sequence2, substitution, gap_open, gap_extend), d_matrix(d_matrix), i_matrix(i_matrix) {};

	friend class d_matrix;
	friend class i_matrix;

protected:
	float gap_cost(int k);

	virtual float getInitialScore(int row, int col);
	virtual cell* getInitialPointer(int row, int col);
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);
};


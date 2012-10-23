#pragma once
#include "matrix.h"

class i_matrix : public matrix
{
private:
	matrix* a_matrix;

public:
	i_matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, float gap_open, float gap_extend) 
		: matrix(sequence1, sequence2, substitution, gap_open, gap_extend) {};

	void set_a_matrix(matrix* a_matrix);
	friend class a_matrix;

protected:
	virtual float getInitialScore(int row, int col);
	virtual cell* getInitialPointer(int row, int col);
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);
};
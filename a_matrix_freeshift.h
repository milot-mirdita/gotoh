#pragma once
#include "a_matrix.h"

class a_matrix_freeshift : public a_matrix
{
protected:
	virtual int get_initial_score(int row, int col);

	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);
	virtual cell* get_traceback_start();

	cell* max_freeshift;
	int max_freeshift_score;
};


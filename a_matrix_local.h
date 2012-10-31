#pragma once
#include "a_matrix.h"
class a_matrix_local : public a_matrix
{
protected:
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);

	virtual bool is_traceback_done(cell* current);
	virtual cell* get_traceback_start();

	cell* max_local;
	int max_local_score;
};


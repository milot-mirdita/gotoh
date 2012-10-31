#include "a_matrix_freeshift.h"
#include "a_matrix.h"

int a_matrix_freeshift::get_initial_score(int row, int col) {
	if(row == 0 && col  > 0) {
			return 0;
	}

	return a_matrix::get_initial_score(row, col);
}

cell* a_matrix_freeshift::get_traceback_start() {
	return max_freeshift;
}

void a_matrix_freeshift::fill_in_cell(cell* current, cell* above, cell* left,
	cell* above_left) {
	a_matrix::fill_in_cell(current, above, left, above_left);

	if(current->score > max_freeshift_score && current->col == cols - 1) {
		max_freeshift_score = current->score;
		max_freeshift = current;
	}
}
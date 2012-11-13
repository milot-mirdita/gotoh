#include "d_matrix.h"
#include <algorithm>

void d_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

int d_matrix::get_initial_score(int row, int col) {
	if(col == 0 && row != 0)
		return min_score;
	
	return 0;
}

void d_matrix::fill_in(int row, int col) {
	int last_index = row * max_size + (col - 1);
	int d_score = cells[last_index] + gap_extend;
	int a_score = a_matrix->cells[last_index] + gap_open + gap_extend;

	cells[last_index + 1] = std::max(a_score, d_score);
}
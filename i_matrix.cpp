#include "i_matrix.h"
#include <algorithm>

void i_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

int i_matrix::get_initial_score(int row, int col) {
	if(row == 0)
		return min_score;
	
	return 0;
}

void i_matrix::fill_in(int row, int col) {
	int last_index = (row - 1) * max_size + col;
	int i_score = cells[last_index] + gap_extend;
	int a_score = a_matrix->cells[last_index] + gap_open + gap_extend;

	cells[last_index + max_size] = std::max(a_score, i_score);
}
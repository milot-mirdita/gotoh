#include "d_matrix.h"
#include <algorithm>

void d_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

int d_matrix::get_initial_score(int row, int col) {
	if(col == 0)
		return min_score;
	
	return 0;
}

void d_matrix::fill_in(int row, int col) {
	int d_score = cells[row * max_size + (col - 1)] + gap_extend;
	int a_score = a_matrix->cells[row * max_size + (col - 1)] + gap_open + gap_extend;

	cells[row * max_size + col] = std::max(a_score, d_score);
}
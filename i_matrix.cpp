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
	int i_score = cells[(row - 1) * max_size + col] + gap_extend;
	int a_score = a_matrix->cells[(row - 1) * max_size + col] + gap_open + gap_extend;

	cells[row * max_size + col] = std::max(a_score, i_score);
}
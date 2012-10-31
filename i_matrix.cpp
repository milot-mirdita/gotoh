#include <climits>
#include <cstdlib>
#include "i_matrix.h"

void i_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

int i_matrix::get_initial_score(int row, int col) {
	if(row == 0)
		return INT_MIN + std::abs(gap_open) + std::abs(gap_extend) + 1;
	
	return 0;
}

void i_matrix::fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) {
	int i_score = above->score + gap_extend;
	int a_score = a_matrix->cells[current->row - 1][current->col].score + gap_open + gap_extend;

	if (a_score >= i_score) {
		current->score = a_score;
	} else {
		current->score = i_score;
	}
}
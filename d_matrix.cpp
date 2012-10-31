#include <climits>
#include <cstdlib>
#include "d_matrix.h"

void d_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

int d_matrix::get_initial_score(int row, int col) {
	if(col == 0)
		return INT_MIN + std::abs(gap_open) + std::abs(gap_extend) + 1;
	
	return 0;
}

void d_matrix::fill_in_cell(cell* current, cell* above, cell* left,
	cell* above_left) {
	int d_score = left->score + gap_extend;
	int a_score = a_matrix->cells[current->row][current->col - 1].score + gap_open + gap_extend;

	if (a_score >= d_score) {
		current->score = a_score;
	} else {
		current->score = d_score;
	}
}
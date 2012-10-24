#include <cfloat>
#include "i_matrix.h"

char i_matrix::get_type() {
	return 'i';
}

void i_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

float i_matrix::get_initial_score(int row, int col) {
	if(row == 0)
		return -FLT_MAX;
	
	return 0;
}

cell* i_matrix::get_initial_pointer(int row, int col) {
	if (row == 0 && col != 0) {
		return &cells[row][col - 1];
	} else {
		return (cell*) 0;
	}
}

void i_matrix::fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) {
	float i_score = above->score + gap_extend;
	float a_score = a_matrix->cells[current->row - 1][current->col].score + gap_open + gap_extend;

	if (a_score >= i_score) {
		current->score = a_score;
		current->previous = &a_matrix->cells[current->row - 1][current->col];
	} else {
		current->score = i_score;
		current->previous = above;
	}
}
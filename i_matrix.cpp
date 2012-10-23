#include <cfloat>
#include "i_matrix.h"

void i_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

float i_matrix::getInitialScore(int row, int col) {
	if(row == 0)
		return -FLT_MAX;
	
	return 0;
}

cell* i_matrix::getInitialPointer(int row, int col) {
	if (row == 0 && col != 0) {
		return &scoreTable[row][col - 1];
	} else {
		return (cell*) 0;
	}
}

void i_matrix::fill_in_cell(cell* current, cell* above, cell* left,
	cell* above_left) {
	float i_score = above->score + gap_extend;
	cell a_cell = a_matrix->scoreTable[current->row - 1][current->col];
	float a_score = a_cell.score + gap_open + gap_extend;

	if (a_score >= i_score) {
		current->score = a_score;
		current->previous = &a_cell;
	} else {
		current->score = i_score;
		current->previous = above;
	}
}
#include <cfloat>
#include "i_matrix.h"

void i_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

float i_matrix::getInitialScore(int row, int col) {
	if(row == 0)
		return FLT_MIN;
	
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
	float d_score = above->score + gap_extend;
	float substitution_score = 0;
	float a_score = a_matrix->scoreTable[current->row - 1][current->col].score + gap_open + gap_extend;

	if (a_score >= d_score) {
		current->score = a_score;
		current->previous = &a_matrix->scoreTable[current->row - 1][current->col];
	} else {
		current->score = d_score;
		current->previous = above;
	}
}
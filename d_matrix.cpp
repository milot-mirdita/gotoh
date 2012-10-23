#include <cfloat>
#include "d_matrix.h"

void d_matrix::set_a_matrix(matrix* a) {
	a_matrix = a;
}

float d_matrix::getInitialScore(int row, int col) {
	if(col == 0)
		return FLT_MIN;
	
	return 0;
}

cell* d_matrix::getInitialPointer(int row, int col) {
	if (col == 0 && row != 0) {
		return &scoreTable[row - 1][col];
	} else {
		return (cell*) 0;
	}
}

void d_matrix::fill_in_cell(cell* current, cell* above, cell* left,
	cell* above_left) {
	float d_score = left->score + gap_extend;
	float substitution_score = 0;
	float a_score = a_matrix->scoreTable[current->row][current->col - 1].score + gap_open + gap_extend;

	if (a_score >= d_score) {
		current->score = a_score;
		current->previous = &a_matrix->scoreTable[current->row][current->col - 1];
	} else {
		current->score = d_score;
		current->previous = left;
	}
}
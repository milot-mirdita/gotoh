#include "a_matrix.h"

float a_matrix::gap_cost(int k) {
	return this->gap_open + this->gap_extend * k;
}

float a_matrix::getInitialScore(int row, int col) {
	if(row == 0 && col == 0)
		return 0;
	if(row == 0 && col  > 0)
		return this->gap_cost(col);
	if(row >  0 && col == 0)
		return this->gap_cost(row);

	return 0;
}


cell* a_matrix::getInitialPointer(int row, int col) {
	if (row == 0 && col != 0) {
		return &scoreTable[row][col - 1];
	} else if (col == 0 && row != 0) {
		return &scoreTable[row - 1][col];
	} else {
		return (cell*) 0;
	}
}

void a_matrix::fill_in_cell(cell* current, cell* above, cell* left,
	cell* above_left) {
	float d_score = d_matrix->scoreTable[current->row][current->col].score;
	float i_score = i_matrix->scoreTable[current->row][current->col].score;
	float substitution_score = 0;
	float a_score = above_left->score + substitution_score;

	if (d_score >= i_score) {
		if (a_score >= d_score) {
			current->score = a_score;
			current->previous = above_left;
		} else {
			current->score = d_score;
			current->previous = &d_matrix->scoreTable[current->row][current->col];
		}
	} else {
		if (a_score >= i_score) {
			current->score = a_score;
			current->previous = above_left;
		} else {
			current->score = i_score;
			current->previous = &i_matrix->scoreTable[current->row][current->col];
		}
	}
}
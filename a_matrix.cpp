#include "a_matrix.h"

float a_matrix::gap_cost(int k) {
	return this->gap_open + this->gap_extend * k;
}

float a_matrix::get_initial_score(int row, int col) {
	if(row == 0 && col == 0)
		return 0;
	if(row == 0 && col  > 0)
		return this->gap_cost(col);
	if(row >  0 && col == 0)
		return this->gap_cost(row);

	return 0;
}


cell* a_matrix::get_initial_pointer(int row, int col) {
	if (row == 0 && col != 0) {
		return &cells[row][col - 1];
	} else if (col == 0 && row != 0) {
		return &cells[row - 1][col];
	} else {
		return (cell*) 0;
	}
}

void a_matrix::fill_in_cell(cell* current, cell* above, cell* left,
	cell* above_left) {
	float d_score = d_matrix->cells[current->row][current->col].score;
	float i_score = i_matrix->cells[current->row][current->col].score;
	float substitution_score = substitution->get_score(sequence1.at(current->row - 1), sequence2.at(current->col - 1));
	float a_score = above_left->score + substitution_score;

	if (d_score >= i_score) {
		if (a_score >= d_score) {
			current->score = a_score;
			current->previous = above_left;
		} else {
			current->score = d_score;
			current->previous = &d_matrix->cells[current->row][current->col];
		}
	} else {
		if (a_score >= i_score) {
			current->score = a_score;
			current->previous = above_left;
		} else {
			current->score = i_score;
			current->previous = &i_matrix->cells[current->row][current->col];
		}
	}
}
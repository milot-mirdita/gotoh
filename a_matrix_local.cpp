#include "a_matrix_local.h"


void a_matrix_local::fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) {
	//FIXME: is this right??
	int d_score = d_matrix->cells[current->row][current->col].score;
	int i_score = i_matrix->cells[current->row][current->col].score;
	int substitution_score = substitution->get_score(sequence1.at(current->row - 1), sequence2.at(current->col - 1));
	int a_score = above_left->score + substitution_score;

	if(std::max(d_score, std::max(i_score, std::max(a_score, 0))) == 0) {
		current->score = 0;
		current->previous = 0;
		return;
	}

	if (d_score >= i_score) {
		if (a_score >= d_score) {
			current->score = a_score;
			current->previous = above_left;
		} else {
			current->score = d_score;
			current->previous = left;
		}
	} else {
		if (a_score >= i_score) {
			current->score = a_score;
			current->previous = above_left;
		} else {
			current->score = i_score;
			current->previous = above;
		}
	}

	if(current->score > max_local_score) {
		max_local_score = current->score;
		max_local = current;
	}
}

bool a_matrix_local::is_traceback_done(cell* current) {
	return current->score == 0.0f || current->previous == 0;
}

cell* a_matrix_local::get_traceback_start() {
	return max_local;
}
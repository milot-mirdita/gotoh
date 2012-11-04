#include "a_matrix_local.h"

int a_matrix_local::get_initial_score(int row, int col) {
	return 0;
}

void a_matrix_local::fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) {
	int d_score = d_matrix->cells[current->row][current->col].score;
	int i_score = i_matrix->cells[current->row][current->col].score;
	int substitution_score = substitution->get_score(sequence1[current->row - 1], sequence2[current->col - 1]);
	int a_score = above_left->score + substitution_score;

	if (d_score >= i_score) {
		if (a_score >= d_score) {
			if(a_score > 0) {
				current->score = a_score;
				current->previous = above_left;
			} else {
				current->score = 0;
				current->previous = 0;
			}
		} else {
			if(d_score > 0) {
				current->score = d_score;
				current->previous = left;
			} else {
				current->score = 0;
				current->previous = 0;
			}
		}
	} else {
		if (a_score >= i_score) {
			if(a_score > 0) {
				current->score = a_score;
				current->previous = above_left;
			} else {
				current->score = 0;
				current->previous = 0;
			}
		} else {
			if(i_score > 0) {
				current->score = i_score;
				current->previous = above;
			} else {
				current->score = 0;
				current->previous = 0;
			}
		}
	}

	if(current->score > max_local_score) {
		max_local_score = current->score;
		max_local = current;
	}
}

bool a_matrix_local::is_traceback_done(cell* current) {
	return current->score == 0 || current->previous == 0;
}

cell* a_matrix_local::get_traceback_start() {
	return max_local;
}

void a_matrix_local::set_sequences(std::string sequence1, std::string sequence2) {
	a_matrix::set_sequences(sequence1, sequence2);

	max_local_score = min_score;
	max_local = 0;
}
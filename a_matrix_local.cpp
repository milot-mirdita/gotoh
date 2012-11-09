#include "a_matrix_local.h"

int a_matrix_local::get_initial_score(int row, int col) {
	return 0;
}

void a_matrix_local::fill_in(int row, int col) {
	int current_index = row * max_size + col;
	int d_score = d_matrix->cells[current_index];
	int i_score = i_matrix->cells[current_index];
	int substitution_score = substitution->get_score(sequence1[row - 1], sequence2[col - 1]);
	int a_score = cells[current_index - max_size - 1] + substitution_score;

	int current_score = cells[current_index] = std::max(0, std::max(a_score, std::max(d_score, i_score)));

	if(current_score > max_local_score) {
		max_local_score = current_score;
		max_local = current_index;
	}
}

bool a_matrix_local::is_traceback_done(int current) {
	int row = current / max_size;
	return cells[current] == 0 || row == 0;	
}

int a_matrix_local::get_traceback_start() {
	return max_local;
}

void a_matrix_local::set_sequences(std::string sequence1, std::string sequence2) {
	a_matrix::set_sequences(sequence1, sequence2);

	max_local_score = min_score;
	max_local = 0;
}
#include "a_matrix_freeshift.h"
#include "a_matrix.h"
#include <climits>

int a_matrix_freeshift::get_initial_score(int row, int col) {
	if(row == 0 && col  > 0) {
			return 0;
	}

	if(row  > 0 && col == 0) {
			return 0;
	}

	return a_matrix::get_initial_score(row, col);
}

int a_matrix_freeshift::get_traceback_start() {
	int max_score = INT_MIN;
	int start = 0;

	for(int i = 0; i < rows; i++) {
		int current_index = i * max_size + (cols - 1);
		int current_score = cells[current_index];
		if(current_score > max_score) {
			max_score = current_score;
			start = current_index;
		}
	}

	for(int i = 0; i < cols; i++) {
		int current_index = (rows - 1) * max_size + i;
		int current_score = cells[current_index];
		if(current_score > max_score) {
			max_score = current_score;
			start = current_index;
		}
	}

	return start;
}
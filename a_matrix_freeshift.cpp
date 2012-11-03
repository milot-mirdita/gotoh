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

cell* a_matrix_freeshift::get_traceback_start() {
	int max_score = INT_MIN;
	cell* start = 0;

	for(int i = 0; i < rows; i++) {
		cell* current = &cells[i][cols - 1];
		if(current->score > max_score) {
			max_score = current->score;
			start = current;
		}
	}

	for(int i = 0; i < cols; i++) {
		cell* current = &cells[rows - 1][i];
		if(current->score > max_score) {
			max_score = current->score;
			start = current;
		}
	}

	return start;
}
#include "i_matrix_123d.h"

void i_matrix_123d::fill_in(int row, int col) {
	unsigned char ss = entries->secondary_structure[row - 1];
	int last_index = (row - 1) * max_size + col;
	int i_score = cells[last_index] + gap_extend * config->scores[2][ss];
	int a_score = a_matrix->cells[last_index] + gap_open * config->scores[1][ss] + gap_extend * config->scores[2][ss];

	cells[last_index + max_size] = std::max(a_score, i_score);
}
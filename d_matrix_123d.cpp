#include "d_matrix_123d.h"

void d_matrix_123d::fill_in(int row, int col) {
	unsigned char ss = entries->secondary_structure[row - 1];
	int last_index = row * max_size + (col - 1);
	int d_score = cells[last_index] + gap_extend * config->scores[2][ss];
	int a_score = a_matrix->cells[last_index] + gap_open * config->scores[1][ss] + gap_extend * config->scores[2][ss];

	cells[last_index + 1] = std::max(a_score, d_score);
}
#include "a_matrix.h"
#include <algorithm>

int a_matrix::gap_cost(int k) {
	return this->gap_open + this->gap_extend * k;
}

int a_matrix::get_initial_score(int row, int col) {
	if(row == 0 && col == 0) {
		return 0;
	} else if(row == 0 && col  > 0) {
		return this->gap_cost(col);
	} else if(row >  0 && col == 0) {
		return this->gap_cost(row);
	}

	return 0;
}


cell* a_matrix::get_initial_pointer(int row, int col) {
	if (row == 0 && col != 0) {
		return &cells[row][col - 1];
	} else if (col == 0 && row != 0) {
		return &cells[row - 1][col];
	}
	
	return 0;
}

void a_matrix::fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) {
	int d_score = d_matrix->cells[current->row][current->col].score;
	int i_score = i_matrix->cells[current->row][current->col].score;
	int substitution_score = substitution->get_score(sequence1[current->row - 1], sequence2[current->col - 1]);
	int a_score = above_left->score + substitution_score;

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
}

std::pair<std::string, std::string> a_matrix::get_traceback() {
	std::string alignment1;
	std::string alignment2;

	cell* current = get_traceback_start();

	int start_rows = rows - 1;
	while(start_rows > current->row) {
		alignment2.push_back(sequence1[start_rows - 1]);
		alignment1.push_back('-');
		start_rows--;
	}

	int start_cols = cols - 1;
	while(start_cols > current->col) {
		alignment1.push_back(sequence2[start_cols - 1]);
		alignment2.push_back('-');
		start_cols--;
	}

	while(is_traceback_done(current) == false) {
		int delta_row = current->row - current->previous->row;
		int delta_col = current->col - current->previous->col;
		if (delta_row == 1 && delta_col == 1) {
			alignment1.push_back(sequence2[current->col - 1]);
			alignment2.push_back(sequence1[current->row - 1]);
		} else if (delta_row == 1 && delta_col == 0) {
			alignment2.push_back(sequence1[current->row - 1]);
			alignment1.push_back('-');
		} else if (delta_row == 0 && delta_col == 1) {
			alignment1.push_back(sequence2[current->col - 1]);
			alignment2.push_back('-');
		}
		current = current->previous;
	}

	int remaining_rows = current->row;
	while(remaining_rows > 0) {
		alignment2.push_back(sequence1[remaining_rows - 1]);
		alignment1.push_back('-');
		remaining_rows--;
	}

	int remaining_cols = current->col;
	while(remaining_cols > 0) {
		alignment1.push_back(sequence2[remaining_cols - 1]);
		alignment2.push_back('-');
		remaining_cols--;
	}

	std::string reverse_alignment1(alignment1);
	std::reverse(reverse_alignment1.begin(), reverse_alignment1.end());

	std::string reverse_alignment2(alignment2);
	std::reverse(reverse_alignment2.begin(), reverse_alignment2.end());

	return std::pair<std::string, std::string>(reverse_alignment1, reverse_alignment2);
}

bool a_matrix::is_traceback_done(cell* current) {
	return current->previous == 0;	
}

cell* a_matrix::get_traceback_start() {
	return &cells[rows - 1][cols - 1];
}
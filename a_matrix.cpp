#include "a_matrix.h"
#include <algorithm>

float a_matrix::gap_cost(int k) {
	return this->gap_open + this->gap_extend * k;
}

char a_matrix::get_type() {
	return 'a';
}

float a_matrix::get_initial_score(int row, int col) {
	if(row == 0 && col == 0)
		return 0;
	if(row == 0 && col  > 0) {
		if(type == alignment_type::FREESHIFT)
			return 0;

		return this->gap_cost(col);
	}
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

	if(type == alignment_type::LOCAL) {
		if(std::max(d_score, std::max(i_score, std::max(a_score, 0.0f))) == 0.0f) {
			current->score = 0;
			current->previous = (cell*)0;
			return;
		}
	}


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

	if(type == alignment_type::LOCAL && current->score > max_local_score) {
		max_local_score = current->score;
		max_local = current;
	}

	if(type == alignment_type::FREESHIFT && current->score > max_freeshift_score && current->col == cols - 1) {
		max_freeshift_score = current->score;
		max_freeshift = current;
	}
}

std::pair<std::string, std::string> a_matrix::get_traceback() {
	std::string alignment1;
	std::string alignment2;

	cell* current = get_traceback_start();
	while(is_traceback_done(current)) {
		// match
		if (current->row - current->previous->row == 1 && current->col - current->previous->col == 1) {
			alignment1.push_back(sequence2.at(current->col - 1));
			alignment2.push_back(sequence1.at(current->row - 1));
			current = current->previous;
		} else if (current->row - current->previous->row == 1 && current->col - current->previous->col == 0) {
			cell* afine = current;
			int k = 0;
			while(afine && afine->type != 'a') {
				alignment2.push_back(sequence1.at(current->row - 1));
				alignment1.push_back('-');
				afine = afine->previous;
				k++;
			}
			current = afine;
		} else if (current->row - current->previous->row == 0 && current->col - current->previous->col == 1) {
			cell* afine = current;
			int k = 0;
			while(afine && afine->type != 'a') {
				alignment1.push_back(sequence2.at(current->col - 1 - k));
				alignment2.push_back('-');
				afine = afine->previous;
				k++;
			}
			current = afine;
		} else {
			current = current->previous;
		}
	}

	std::string reverse_alignment1(alignment1);
	std::reverse(reverse_alignment1.begin(), reverse_alignment1.end());

	std::string reverse_alignment2(alignment2);
	std::reverse(reverse_alignment2.begin(), reverse_alignment2.end());



	return std::pair<std::string, std::string>(reverse_alignment1, reverse_alignment2);
}

bool a_matrix::is_traceback_done(cell* current) {
	switch(type) {
	case alignment_type::LOCAL:
		return current->score == 0.0f || current->previous == (cell*)0;
	case alignment_type::GLOBAL:
	case alignment_type::FREESHIFT:
		return !!current->previous;	
	}
	return true;
}

cell* a_matrix::get_traceback_start() {
	switch(type) {
	case alignment_type::LOCAL:
		return max_local;
	case alignment_type::GLOBAL:
		return &cells[rows - 1][cols - 1];
	case alignment_type::FREESHIFT:
		return max_freeshift;
		
	}
	return (cell*) 0;
}
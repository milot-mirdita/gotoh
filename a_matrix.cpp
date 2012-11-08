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

void a_matrix::fill_in(int row, int col) {
	int current_index = row * max_size + col;
	int d_score = d_matrix->cells[current_index];
	int i_score = i_matrix->cells[current_index];
	int substitution_score = substitution->get_score(sequence1[row - 1], sequence2[col - 1]);
	int a_score = cells[(row - 1) * max_size + (col - 1)] + substitution_score;

	cells[current_index] = std::max(a_score, std::max(d_score, i_score));
}

std::pair<std::string, std::string> a_matrix::get_traceback() {
	std::string alignment1;
	std::string alignment2;

	int current = get_traceback_start();

	//int start_rows = rows - 1;
	//while(start_rows > current->row) {
	//	alignment2.push_back(sequence1[start_rows - 1]);
	//	alignment1.push_back('-');
	//	start_rows--;
	//}

	//int start_cols = cols - 1;
	//while(start_cols > current->col) {
	//	alignment1.push_back(sequence2[start_cols - 1]);
	//	alignment2.push_back('-');
	//	start_cols--;
	//}

	/*while(is_traceback_done(current) == false) {
		int delta_row = current->row - current->previous->row;
		int delta_col = current->col - current->previous->col;
		if (delta_row == 1 && delta_col == 1) {
			alignment1.push_back(sequence2[current->col - 1]);
			alignment2.push_back(sequence1[current->row - 1]);
			current = current->previous;
		} else if (delta_row == 1 && delta_col == 0) {
			int counter = 0;
			cell* temp = 0;
			cell* afine = current->previous;
            do {
                alignment2.push_back(sequence1[afine->row - 1]);
				alignment1.push_back('-');
				temp = afine;
				cell* temp = afine;
                afine = afine->previous;
				if(is_traceback_done(afine))
					break;

				counter++;
			} while (current->score != temp->score + gap_open + (counter - 1) * gap_extend );   
            current = afine;
		} else if (delta_row == 0 && delta_col == 1) {
			int counter = 0;
			cell* temp = 0;
			cell* afine = current->previous;
            do {
				alignment1.push_back(sequence2[afine->col - 1]);
				alignment2.push_back('-');
				temp = afine;
                afine = afine->previous;
				if(is_traceback_done(afine))
					break;
				counter++;
			} while (current->score != temp->score + gap_open + (counter - 1) * gap_extend );   
            current = afine;
		}
	}*/

	//int remaining_rows = current->row;
	//while(remaining_rows > 0) {
	//	alignment2.push_back(sequence1[remaining_rows - 1]);
	//	alignment1.push_back('-');
	//	remaining_rows--;
	//}

	//int remaining_cols = current->col;
	//while(remaining_cols > 0) {
	//	alignment1.push_back(sequence2[remaining_cols - 1]);
	//	alignment2.push_back('-');
	//	remaining_cols--;
	//}

	std::string reverse_alignment1(alignment1);
	std::reverse(reverse_alignment1.begin(), reverse_alignment1.end());

	std::string reverse_alignment2(alignment2);
	std::reverse(reverse_alignment2.begin(), reverse_alignment2.end());

	return std::pair<std::string, std::string>(reverse_alignment2, reverse_alignment1);
}

bool a_matrix::is_traceback_done(int current) {
	int row = current / max_size;
	int col = current % max_size;
	return row == 0 && col == 0;	
}

int a_matrix::get_traceback_start() {
	return (rows - 1) * max_size + (cols - 1);
}
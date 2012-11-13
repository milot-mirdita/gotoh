#include "a_matrix_123d.h"
#include <algorithm>
#include <string>

int a_matrix_123d::get_initial_score(int row, int col) {
	return 0;
}

void a_matrix_123d::fill_in(int row, int col) {
	unsigned char ss = entries->secondary_structure[row - 1];
	int alpha = config->scores[0][ss];
	int beta = config->scores[3][ss];
	int gamma_g = config->scores[4][ss];
	int gamma_l = config->scores[5][ss];

	unsigned char aa = sequence2[col - 1] - 65;
	int global_contacts = entries->global_contacts[row - 1];
	int local_contacts = entries->local_contacts[row - 1];

	int current_index = row * max_size + col;
	int d_score = d_matrix->cells[current_index];
	int i_score = i_matrix->cells[current_index];
	int substitution_score = substitution->get_score(sequence1[row - 1], sequence2[col - 1]);
	int match = alpha * substitution_score 
		+ beta * secondary_pref->get_score(ss, aa)
		+ gamma_g * contact_pref->matrix_lookup[ss][aa][global_contacts]
		+ gamma_l * contact_pref->matrix_lookup[ss][aa][local_contacts];
	int a_score = cells[current_index - max_size - 1] + match;

	cells[current_index] = std::max(a_score, std::max(d_score, i_score));
}

std::pair<std::string, std::string> a_matrix_123d::get_traceback() {
	std::string alignment1;
	std::string alignment2;

	int current = get_traceback_start();
	int current_row = current / max_size;
	int current_col = current % max_size;
	int start_rows = rows - 1;
	while(start_rows > current_row) {
		alignment2.push_back(sequence1[start_rows - 1]);
		alignment1.push_back('-');
		start_rows--;
	}

	int start_cols = cols - 1;
	while(start_cols > current_col) {
		alignment1.push_back(sequence2[start_cols - 1]);
		alignment2.push_back('-');
		start_cols--;
	}

	while(is_traceback_done(current) == false) {
		current_row = current / max_size;
		current_col = current % max_size;

		unsigned char ss = entries->secondary_structure[current_row - 1];
		int alpha = config->scores[0][ss];
		int beta = config->scores[3][ss];
		int gamma_g = config->scores[4][ss];
		int gamma_l = config->scores[5][ss];

		unsigned char aa = sequence2[current_col - 1] - 65;
		int global_contacts = entries->global_contacts[current_row - 1];
		int local_contacts = entries->local_contacts[current_row - 1];

		int above_left_index = (current_row - 1) * max_size + (current_col - 1);
		if ((current_row != 0 && current_col != 0) 
			&& cells[current] == cells[above_left_index] 
		+ alpha * substitution->get_score(sequence1[current_row - 1], sequence2[current_col - 1])
		+ beta * secondary_pref->get_score(ss, aa)
		+ gamma_g * contact_pref->matrix_lookup[ss][aa][global_contacts]
		+ gamma_l * contact_pref->matrix_lookup[ss][aa][local_contacts]) {
			alignment1.push_back(sequence2[current_col - 1]);
			alignment2.push_back(sequence1[current_row - 1]);
			current = above_left_index;
		} else if (cells[current] == i_matrix->cells[current]) {
			int counter = 0;
			int last_gap_cost = 0;
			int current_gap_cost = 0;
			do {
				counter++;

				alignment1.push_back('-');
				alignment2.push_back(sequence1[current_row - counter]);

				const unsigned char current_ss = entries->secondary_structure[current_row - counter];
				const int current_gap_extend = gap_extend * config->scores[2][current_ss];
				const int current_gap_open   = gap_open   * config->scores[1][current_ss];
				current_gap_cost  += current_gap_open + current_gap_extend - last_gap_cost;
				last_gap_cost = current_gap_open;
			} while (cells[current] != 
				cells[(current_row - counter) * max_size + current_col] + current_gap_cost);   
			current -= counter * max_size;
		} else if (cells[current] == d_matrix->cells[current]) {
			int counter = 0;

			const int current_gap_extend = gap_extend * config->scores[2][ss];
			const int current_gap_open   = gap_open   * config->scores[1][ss] + current_gap_extend;
			do {
				counter++;

				alignment1.push_back(sequence2[current_col - counter]);
				alignment2.push_back('-');
			} while (cells[current] != 
				cells[current_row * max_size + (current_col - counter)] 
				+ current_gap_open + (counter - 1) * current_gap_extend);   
			current -= counter;
		}
	}

	int remaining_rows = current / max_size;
	while(remaining_rows > 0) {
		alignment2.push_back(sequence1[remaining_rows - 1]);
		alignment1.push_back('-');
		remaining_rows--;
	}

	int remaining_cols = current % max_size;
	while(remaining_cols > 0) {
		alignment1.push_back(sequence2[remaining_cols - 1]);
		alignment2.push_back('-');
		remaining_cols--;
	}

	std::string reverse_alignment1(alignment1);
	std::reverse(reverse_alignment1.begin(), reverse_alignment1.end());

	std::string reverse_alignment2(alignment2);
	std::reverse(reverse_alignment2.begin(), reverse_alignment2.end());

	return std::pair<std::string, std::string>(reverse_alignment2, reverse_alignment1);
}

void a_matrix_123d::init( void )
{

}

void a_matrix_123d::set_sscc( sscc_entries* sscc )
{
	this->entries = sscc;

	unsigned char ss = entries->secondary_structure[0];
	int current_gap_extend = 0;
	int current_gap_open = gap_open * config->scores[1][ss];
	for(int i = 1; i < rows; i++) {
		ss = entries->secondary_structure[i - 1];
		current_gap_extend += gap_extend * config->scores[2][ss];
		cells[i * max_size] = current_gap_open + current_gap_extend;
		i_matrix->cells[i * max_size] = current_gap_open + current_gap_extend;
		d_matrix->cells[i * max_size] = min_score;
	}

	for(int i = 1; i < cols; i++) {
		cells[i] = gap_open * config->scores[1][2] + gap_extend * config->scores[2][2] * i;
		d_matrix->cells[i] = gap_open * config->scores[1][2] + gap_extend * config->scores[2][2] * i;
		i_matrix->cells[i] = min_score;
	}
}

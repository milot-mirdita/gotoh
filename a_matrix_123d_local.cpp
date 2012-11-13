#include "a_matrix_123d_local.h"
#include "a_matrix_123d.h"

int a_matrix_123d_local::get_initial_score(int row, int col) {
	return 0;
}

void a_matrix_123d_local::fill_in(int row, int col) {
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

	int current_score = cells[current_index] = std::max(0, std::max(a_score, std::max(d_score, i_score)));

	if(current_score > max_local_score) {
		max_local_score = current_score;
		max_local = current_index;
	}
}

bool a_matrix_123d_local::is_traceback_done(int current) {
	int row = current / max_size;
	return cells[current] == 0 || row == 0;	
}

int a_matrix_123d_local::get_traceback_start() {
	return max_local;
}

void a_matrix_123d_local::set_sequences(std::string sequence1, std::string sequence2) {
	a_matrix_123d::set_sequences(sequence1, sequence2);

	max_local_score = min_score;
	max_local = 0;
}

void a_matrix_123d_local::set_sscc( sscc_entries* sscc )
{
	this->entries = sscc;
	initialize_scores();
}
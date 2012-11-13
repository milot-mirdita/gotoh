#pragma once
#include "a_matrix_123d.h"
#include "a_matrix_freeshift.h"

class a_matrix_123d_freeshift : public a_matrix_123d {
public:
	a_matrix_123d_freeshift(unsigned int size, substitution_matrix* substitution,
		int gap_open, int gap_extend, matrix* d_matrix, matrix* i_matrix, 
		config_123d* config, contact_preferences* contact_pref, secondary_structure_preference* secondary_pref) 
		: a_matrix_123d(size, substitution, gap_open, gap_extend, d_matrix, i_matrix, config, contact_pref, secondary_pref) {
			min_score = INT_MIN + std::abs(gap_open) * std::max(config->scores[1][0], std::max(config->scores[1][1], config->scores[1][2])) + std::abs(gap_extend) *std::max(config->scores[2][0], std::max(config->scores[2][1], config->scores[2][2])) + 1;
	};

	virtual void set_sscc(sscc_entries* sscc);

protected:
	virtual int get_initial_score(int row, int col);
	virtual int get_traceback_start();
	virtual bool is_traceback_done(int current);
};


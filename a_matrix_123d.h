#pragma once
#include "a_matrix.h"
#include "config_123d.h"
#include "secondary_structure_contacts.h"
#include "contact_preferences.h"
#include "secondary_structure_preference.h"
#include <climits>

class a_matrix_123d :
	public a_matrix
{
protected:
	config_123d* config;
	sscc_entries* entries;
	contact_preferences* contact_pref;
	secondary_structure_preference* secondary_pref;

public:
	a_matrix_123d(unsigned int size, substitution_matrix* substitution,
		int gap_open, int gap_extend, matrix* d_matrix, matrix* i_matrix, 
		config_123d* config, contact_preferences* contact_pref, secondary_structure_preference* secondary_pref) 
		: a_matrix(size, substitution, gap_open, gap_extend, d_matrix, i_matrix), 
		config(config), contact_pref(contact_pref), secondary_pref(secondary_pref) {
		min_score = INT_MIN + std::abs(gap_open) * std::max(config->scores[1][0], std::max(config->scores[1][1], config->scores[1][2])) + std::abs(gap_extend) *std::max(config->scores[2][0], std::max(config->scores[2][1], config->scores[2][2])) + 1;
	};

	virtual void set_sscc(sscc_entries* sscc);

	virtual void init(void);

	virtual void fill_in(int row, int col);
	std::pair<std::string, std::string> get_traceback();
	virtual int get_initial_score(int row, int col);
};


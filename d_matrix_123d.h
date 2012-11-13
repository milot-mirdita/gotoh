#pragma once
#include "d_matrix.h"
#include "secondary_structure_contacts.h"
#include "config_123d.h"
#include <climits>

class d_matrix_123d : public d_matrix
{
protected:
	config_123d* config;
	sscc_entries* entries;

public:
	d_matrix_123d(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend, config_123d* config) 
		: d_matrix(size, substitution, gap_open, gap_extend), config(config) {
			min_score = INT_MIN + std::abs(gap_open) * std::max(config->scores[1][0], std::max(config->scores[1][1], config->scores[1][2])) + std::abs(gap_extend) *std::max(config->scores[2][0], std::max(config->scores[2][1], config->scores[2][2])) + 1;
	};
	void set_sscc(sscc_entries* sscc) {
		this->entries = sscc;
	}

	virtual void fill_in(int row, int col);
};


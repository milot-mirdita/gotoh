#pragma once
#include "gotoh.h"
#include "secondary_structure_contacts.h"
#include "config_123d.h"
#include "secondary_structure_preference.h"
#include "contact_preferences.h"

class one_two_three_d : public gotoh
{
public:
	one_two_three_d( unsigned int size, int gap_open, int gap_extend, substitution_matrix* matrix, std::string alignment_type, config_123d* config, contact_preferences* contact_pref, secondary_structure_preference* secondary_pref);
	void set_sscc(sscc_entries* sscc);
	float get_score();
};


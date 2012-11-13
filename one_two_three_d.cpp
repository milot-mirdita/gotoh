#include "one_two_three_d.h"
#include "a_matrix_123d.h"
#include "a_matrix_123d_freeshift.h"
#include "a_matrix_123d_local.h"
#include "i_matrix_123d.h"
#include "d_matrix_123d.h"

one_two_three_d::one_two_three_d(unsigned int size, int gap_open, int gap_extend, substitution_matrix* matrix, std::string alignment_type, config_123d* config, contact_preferences* contact_pref, secondary_structure_preference* secondary_pref)
	: gotoh(size, gap_open, gap_extend, matrix, alignment_type) {
	dm = new d_matrix_123d(size, matrix, gap_open, gap_extend, config);
	im = new i_matrix_123d(size, matrix, gap_open, gap_extend, config);

	if(alignment_type.find("local") != std::string::npos) {
		am = new a_matrix_123d_local(size, matrix, gap_open, gap_extend, dm, im, config, contact_pref, secondary_pref);
		dm->init();
		im->init();
	} else if (alignment_type.find("freeshift") != std::string::npos) {
		am = new a_matrix_123d_freeshift(size, matrix, gap_open, gap_extend, dm, im, config, contact_pref, secondary_pref);
		dm->init();
		im->init();
	} else if (alignment_type.find("global") != std::string::npos) {
		am = new a_matrix_123d(size, matrix, gap_open, gap_extend, dm, im, config, contact_pref, secondary_pref);
	}

	am->init();

	dm->set_a_matrix(am);
	im->set_a_matrix(am);
}

void one_two_three_d::set_sscc( sscc_entries* sscc )
{
	am->set_sscc(sscc);
	dm->set_sscc(sscc);
	im->set_sscc(sscc);
}

float one_two_three_d::get_score() {
	int score_cell = am->get_traceback_start();
	return (float) am->cells[score_cell] / 1000000;
}
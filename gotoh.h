#pragma once
#include <string>
#include "substitution_matrix.h"
#include "a_matrix.h"
#include "d_matrix.h"
#include "i_matrix.h"

class gotoh
{
private:
	a_matrix* am;
	d_matrix* dm;
	i_matrix* im;

protected:
	const unsigned int size;
	const int gap_open;
	const int gap_extend;
	substitution_matrix* matrix;
	std::string alignment_type;

public:
	gotoh(unsigned int size, int gap_open, int gap_extend, substitution_matrix* matrix, std::string alignment_type);
	~gotoh();
	void run(std::string sequence1, std::string sequence2);
	void print_matrices(std::string type);
	std::pair<std::string, std::string> get_alignment();
	float get_score(std::pair<std::string, std::string> alignment, std::string type);
	float get_score();
};


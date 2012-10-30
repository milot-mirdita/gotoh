#pragma once
#include <string>
#include "substitution_matrix.h"

class gotoh
{
public:
	gotoh(std::string sequence1, std::string sequence2, float gap_open, float gap_extend, substitution_matrix* matrix);
};


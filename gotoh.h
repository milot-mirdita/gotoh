#pragma once
#include <string>
#include "substitution_matrix.h"

class gotoh
{
private:
	std::string sequence1;
	std::string sequence2;

public:
	gotoh(std::string sequence1, std::string sequence2, substitution_matrix* matrix);
	~gotoh(void);
};


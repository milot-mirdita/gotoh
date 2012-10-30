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
	unsigned int size;
	float gap_open;
	float gap_extend;
	substitution_matrix* matrix;

public:
	gotoh(unsigned int size, float gap_open, float gap_extend, substitution_matrix* matrix);
	~gotoh();
	void run(std::string sequence1, std::string sequence2);
};


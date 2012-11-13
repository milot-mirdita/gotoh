#pragma once
#include "matrix.h"

class i_matrix : public matrix
{
protected:
	matrix* a_matrix;

public:
	i_matrix(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend) 
		: matrix(size, substitution, gap_open, gap_extend) {};

	void set_a_matrix(matrix* a_matrix);
	friend class a_matrix;

	virtual void fill_in(int row, int col);

protected:
	virtual int get_initial_score(int row, int col);

private:
	virtual std::pair<std::string, std::string> get_traceback() { return std::pair<std::string, std::string>(); };
	virtual bool is_traceback_done(int current) { return false; };
	virtual int get_traceback_start() { return 0; };
};
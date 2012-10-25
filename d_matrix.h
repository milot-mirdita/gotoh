#pragma once
#include "matrix.h"

class d_matrix : public matrix
{
private:
	matrix* a_matrix;

public:
	d_matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, float gap_open, float gap_extend) 
		: matrix(sequence1, sequence2, substitution, gap_open, gap_extend) {};

	void set_a_matrix(matrix* a_matrix);
	friend class a_matrix;

protected:
	virtual float get_initial_score(int row, int col);
	virtual cell* get_initial_pointer(int row, int col) { return 0; };
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);

private:
	virtual std::pair<std::string, std::string> get_traceback() { return std::pair<std::string, std::string>(); };
	virtual bool is_traceback_done(cell* current) { return false; };
	virtual cell* get_traceback_start() { return 0; };
};

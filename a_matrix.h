#pragma once
#include "matrix.h"
#include "alignment_type.h"


class a_matrix : public matrix
{
private:
	matrix* d_matrix;
	matrix* i_matrix;
	alignment_type type;

public:
	a_matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, alignment_type type,
		float gap_open, float gap_extend, matrix* d_matrix, matrix* i_matrix) 
		: matrix(sequence1, sequence2, substitution, gap_open, gap_extend), d_matrix(d_matrix), i_matrix(i_matrix), type(type) {};

	virtual std::pair<std::string, std::string> get_traceback();

	friend class d_matrix;
	friend class i_matrix;

protected:
	float gap_cost(int k);

	virtual char get_type();
	virtual float get_initial_score(int row, int col);
	virtual cell* get_initial_pointer(int row, int col);
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left);

	virtual bool is_traceback_done(cell* current);
	virtual cell* get_traceback_start();

	cell* max_local;
	cell* max_freeshift;

	float max_local_score;
	float max_freeshift_score;
};


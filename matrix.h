#pragma once
#include "cell.h"
#include "substitution_matrix.h"
#include <string>

class matrix {
public:
	matrix(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend);
	~matrix();

	void init(void);

	virtual void set_sequences(std::string sequence1, std::string sequence2);
	void fill_in(int row, int col);

	virtual std::pair<std::string, std::string> get_traceback() = 0;

	void print(void);
	void print_html(void);

	int rows;
	int cols;

	unsigned int max_size;
	int gap_open;
	int gap_extend;

	std::string sequence1;
	std::string sequence2;

	cell** cells;	

protected:
	void initialize_scores(void);
	void initialize_pointers(void);

	virtual int get_initial_score(int row, int col) = 0;
	virtual cell* get_initial_pointer(int row, int col) = 0;
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) = 0;

	virtual bool is_traceback_done(cell* current) = 0;
	virtual cell* get_traceback_start() = 0;

	substitution_matrix* substitution;
};
#pragma once
#include "substitution_matrix.h"
#include "secondary_structure_contacts.h"
#include <string>

class matrix {
public:
	matrix(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend);
	~matrix();

	virtual void init(void);

	virtual void set_sequences(std::string sequence1, std::string sequence2);
	virtual void set_sscc(sscc_entries* sscc) {}
	virtual void fill_in(int row, int col) = 0;

	virtual std::pair<std::string, std::string> get_traceback() = 0;

	void print(void);
	void print_html(void);

	int rows;
	int cols;

	const unsigned int max_size;
	const int gap_open;
	const int gap_extend;

	char* sequence1;
	char* sequence2;

	int* cells;	

protected:
	void initialize_scores(void);

	virtual int get_initial_score(int row, int col) = 0;

	virtual bool is_traceback_done(int current) = 0;
	virtual int get_traceback_start() = 0;

	substitution_matrix* substitution;

	int min_score;
};
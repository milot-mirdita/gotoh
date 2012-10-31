#pragma once
#include <string>

class substitution_matrix
{
public:
	substitution_matrix(std::string file, float scale_factor);
	~substitution_matrix(void);

	int get_score(char residue1, char residue2);
	void print(void);

	int rows;
	int cols;

	float scale_factor;

	char row_index[256];
	char col_index[256];

private:
	int current_row_index;

	int** scores;

	void parse_index_row(std::string index);
	void parse_index_col(std::string index);

	void normalize(void);
};


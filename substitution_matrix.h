#pragma once
#include <string>

class substitution_matrix
{
public:
	substitution_matrix(std::string file);
	~substitution_matrix(void);

	float get_score(char residue1, char residue2);
	void print(void);

	int rows;
	int cols;

	char row_index[256];
	char col_index[256];

private:
	int current_row_index;

	float** scores;

	void parse_index_row(std::string index);
	void parse_index_col(std::string index);

	void normalize(void);
};


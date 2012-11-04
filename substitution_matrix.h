#pragma once
#include <string>

class substitution_matrix
{
public:
	substitution_matrix(std::string file, float scale_factor);
	~substitution_matrix(void);

	inline int get_score(unsigned char residue1, unsigned char residue2) {
		return scores[row_index[residue1]][col_index[residue2]];
	}

	void print(void);

	int rows;
	int cols;

	float scale_factor;

	unsigned char row_index[256];
	unsigned char col_index[256];

private:
	int current_row_index;

	int** scores;

	void parse_index_row(std::string index);
	void parse_index_col(std::string index);

	void normalize(void);
};


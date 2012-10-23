#pragma once
#include "cell.h"
#include "substitution_matrix.h"
#include <string>

class matrix {
public:
	matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, float gap_open, float gap_extend);
	~matrix();

	void init(void);

	void fill_in(int row, int col);

	int rows;
	int cols;
	float gap_open;
	float gap_extend;

	std::string sequence1;
	std::string sequence2;

	cell** scoreTable;	

protected:
	void initializeScores(void);
	void initializePointers(void);

	virtual float getInitialScore(int row, int col) = 0;
	virtual cell* getInitialPointer(int row, int col) = 0;
	virtual void fill_in_cell(cell* current, cell* above, cell* left, cell* above_left) = 0;

	substitution_matrix* substitution;
};
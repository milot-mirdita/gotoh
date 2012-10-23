#include "matrix.h"
#include <iostream>

matrix::matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, float gap_open, float gap_extend) 
	: sequence1(sequence1), sequence2(sequence2), gap_open(gap_open), gap_extend(gap_extend), substitution(substitution) {
	rows = sequence1.length() + 1;
	cols = sequence2.length() + 1;

	scoreTable = new cell*[rows];
	for (int i = 0; i < rows; i++) {
		scoreTable[i] = new cell[cols];
		for (int j = 0; j < cols; j++) {
			scoreTable[i][j] = cell(i,j);
		}
	}
}

void matrix::init() {
	initializeScores();
	initializePointers();
}

matrix::~matrix() {
	for (int i = 0; i < rows; i++) {
		delete scoreTable[i];
	}
	delete scoreTable;
}

void matrix::initializeScores() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scoreTable[i][j].score = getInitialScore(i, j);
		}
	}
}

void matrix::initializePointers() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scoreTable[i][j].previous = getInitialPointer(i, j);
		}
	}
}

void matrix::fill_in(int row, int col) {
	cell* currentCell = &scoreTable[row][col];
	cell* cellAbove = &scoreTable[row - 1][col];
	cell* cellToLeft = &scoreTable[row][col - 1];
	cell* cellAboveLeft = &scoreTable[row - 1][col - 1];
	fill_in_cell(currentCell, cellAbove, cellToLeft, cellAboveLeft);
}

void matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << scoreTable[i][j].score << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	 
}
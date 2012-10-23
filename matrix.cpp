#include "matrix.h"
#include <iostream>

matrix::matrix(std::string sequence1, std::string sequence2, substitution_matrix* substitution, float gap_open, float gap_extend) 
	: sequence1(sequence1), sequence2(sequence2), gap_open(gap_open), gap_extend(gap_extend), substitution(substitution) {
	rows = sequence1.length() + 1;
	cols = sequence2.length() + 1;

	cells = new cell*[rows];
	for (int i = 0; i < rows; i++) {
		cells[i] = new cell[cols];
		for (int j = 0; j < cols; j++) {
			cells[i][j] = cell(i,j);
		}
	}
}

void matrix::init() {
	initialize_scores();
	initialize_pointers();
}

matrix::~matrix() {
	for (int i = 0; i < rows; i++) {
		delete cells[i];
	}
	delete cells;
}

void matrix::initialize_scores() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cells[i][j].score = get_initial_score(i, j);
		}
	}
}

void matrix::initialize_pointers() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cells[i][j].previous = get_initial_pointer(i, j);
		}
	}
}

void matrix::fill_in(int row, int col) {
	cell* currentCell = &cells[row][col];
	cell* cellAbove = &cells[row - 1][col];
	cell* cellToLeft = &cells[row][col - 1];
	cell* cellAboveLeft = &cells[row - 1][col - 1];
	fill_in_cell(currentCell, cellAbove, cellToLeft, cellAboveLeft);
}

void matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << cells[i][j].score << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	 
}
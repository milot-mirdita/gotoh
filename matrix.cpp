#include "matrix.h"
#include <iostream>

matrix::matrix(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend) 
	: gap_open(gap_open), gap_extend(gap_extend), substitution(substitution), max_size(size + 1) {
	cells = new cell*[max_size];
	for (unsigned int i = 0; i < max_size; i++) {
		cells[i] = new cell[max_size];
		for (unsigned int j = 0; j < max_size; j++) {
			cell c = {0, 0, i, j};
			cells[i][j] = c;
		}
	}
}

matrix::~matrix() {
	for (unsigned int i = 0; i < max_size; i++) {
		delete cells[i];
	}
	delete cells;
}

void matrix::init() {
	initialize_scores();
	initialize_pointers();
}

void matrix::initialize_scores() {
	for (unsigned int i = 0; i < max_size; i++) {
		for (unsigned int j = 0; j < max_size; j++) {
			cells[i][j].score = get_initial_score(i, j);
		}
	}
}

void matrix::initialize_pointers() {
	for (unsigned int i = 0; i < max_size; i++) {
		for (unsigned int j = 0; j < max_size; j++) {
			cells[i][j].previous = get_initial_pointer(i, j);
		}
	}
}

void matrix::set_sequences(std::string sequence1, std::string sequence2) {
	this->sequence1 = sequence1;
	this->sequence2 = sequence2;

	rows = sequence1.length() + 1;
	cols = sequence2.length() + 1;
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
			std::cout << cells[i][j].score / substitution->scale_factor << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	 
}
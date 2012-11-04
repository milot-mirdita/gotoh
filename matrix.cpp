#include "matrix.h"
#include <iostream>

matrix::matrix(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend) 
	: max_size(size + 1), gap_open(gap_open), gap_extend(gap_extend), substitution(substitution), 
	min_score(INT_MIN + std::abs(gap_open) + std::abs(gap_extend) + 1) {
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

	delete[] sequence1;
	delete[] sequence2;
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
	this->sequence1 = new char [sequence1.size()+1];
	strcpy_s(this->sequence1, sequence1.size()+1, sequence1.c_str());

	this->sequence2 = new char [sequence2.size()+1];
	strcpy_s(this->sequence2, sequence2.size()+1, sequence2.c_str());

	rows = sequence1.size() + 1;
	cols = sequence2.size() + 1;
}

void matrix::fill_in(int row, int col) {
	cell* currentCell = &cells[row][col];
	cell* cellAbove = &cells[row - 1][col];
	cell* cellToLeft = &cells[row][col - 1];
	cell* cellAboveLeft = &cells[row - 1][col - 1];
	fill_in_cell(currentCell, cellAbove, cellToLeft, cellAboveLeft);
}

void matrix::print() {
	std::cout << " \t \t";
	for(int i = 1; i < rows; i++) {
		std::cout << sequence1[i - 1] << '\t';
	}
	std::cout << std::endl;

	for (int i = 0; i < rows; i++) {
		if(i == 0) {
			std::cout << " \t";
		}
		if(i > 0) {
			std::cout << sequence2[i - 1] << '\t';
		}
		for (int j = 0; j < cols; j++) {
			std::cout << cells[i][j].score / substitution->scale_factor << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	 
}

void matrix::print_html() {
	std::cout << "<table>" << std::endl;
	std::cout << "<thead><tr><td></td><td></td>" << std::endl;
	for(int i = 1; i < rows; i++) {
		std::cout << "<th>" << sequence1[i - 1] << "</th>" << std::endl;
	}
	std::cout << "</tr></thead>" << std::endl;
	std::cout << "<tbody>" << std::endl;
	for (int i = 0; i < rows; i++) {
		std::cout << "<tr>" << std::endl;
		if(i == 0) {
			std::cout << "<td></td>";
		}
		if(i > 0) {
			std::cout << "<td>" << sequence2[i - 1] << "</td>" << std::endl;
		}
		for (int j = 0; j < cols; j++) {
			std::cout << "<td>" << cells[i][j].score / substitution->scale_factor << "</td>" << std::endl;
		}
		std::cout << "</tr>" << std::endl;
		std::cout << "</tbody>" << std::endl;
	}
	std::cout << "</table>" << std::endl;	 
}
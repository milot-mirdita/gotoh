#include "matrix.h"
#include <iostream>
#include <climits>
#include <cstdlib>

matrix::matrix(unsigned int size, substitution_matrix* substitution, int gap_open, int gap_extend) 
	: max_size(size + 1), gap_open(gap_open), gap_extend(gap_extend), substitution(substitution), 
	min_score(INT_MIN + std::abs(gap_open) + std::abs(gap_extend) + 1) {
	cells = new int[max_size * max_size];
	sequence1 = 0;
	sequence2 = 0;
}

matrix::~matrix() {
	delete[] cells;
	if(this->sequence1)
		delete[] sequence1;
	if(this->sequence2)
		delete[] sequence2;
}

void matrix::init() {
	initialize_scores();
}

void matrix::initialize_scores() {
	for (unsigned int i = 0; i < max_size; i++) {
		cells[i * max_size] = get_initial_score(i, 0);
	}
	for (unsigned int i = 0; i < max_size; i++) {
		cells[i] = get_initial_score(0, i);
	}
}

void matrix::set_sequences(std::string sequence1, std::string sequence2) {
// dont want to maintain a different version for vc++ and g++
#pragma warning( disable : 4996 )
	if(this->sequence1)
		delete[] this->sequence1;
	this->sequence1 = new char [sequence1.size()+1];
	sequence1.copy(this->sequence1, sequence1.size()+1, 0);

	if(this->sequence2)
		delete[] this->sequence2;
	this->sequence2 = new char [sequence2.size()+1];
	sequence2.copy(this->sequence2, sequence2.size()+1, 0);

	rows = sequence1.size() + 1;
	cols = sequence2.size() + 1;
}

void matrix::print() {
#ifdef ONETWOTHREED
	float scale = 10000.0f;
#else
	float scale = matrix->scale_factor;
#endif

	std::cout << " \t \t";
	for(int i = 1; i < cols; i++) {
		std::cout << sequence2[i - 1] << '\t';
	}
	std::cout << std::endl;

	for (int i = 0; i < rows; i++) {
		if(i == 0) {
			std::cout << " \t";
		}
		if(i > 0) {
			std::cout << sequence1[i - 1] << '\t';
		}
		for (int j = 0; j < cols; j++) {
			std::cout << cells[i * max_size + j] / scale << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	 
}

void matrix::print_html() { 
#ifdef ONETWOTHREED
	float scale = 10000.0f;
#else
	float scale = matrix->scale_factor;
#endif

	std::cout << "<table border=\"1\">" << std::endl;
	std::cout << "<thead><tr><td></td><td></td>" << std::endl;
	for(int i = 1; i < cols; i++) {
		std::cout << "<th>" << sequence2[i - 1] << "</th>" << std::endl;
	}
	std::cout << "</tr></thead>" << std::endl;
	std::cout << "<tbody>" << std::endl;
	for (int i = 0; i < rows; i++) {
		std::cout << "<tr>" << std::endl;
		if(i == 0) {
			std::cout << "<td></td>";
		}
		if(i > 0) {
			std::cout << "<td>" << sequence1[i - 1] << "</td>" << std::endl;
		}
		for (int j = 0; j < cols; j++) {
			std::cout << "<td>" << cells[i * max_size + j] / scale << "</td>" << std::endl;
		}
		std::cout << "</tr>" << std::endl;
		std::cout << "</tbody>" << std::endl;
	}
	std::cout << "</table>" << std::endl;	 
}
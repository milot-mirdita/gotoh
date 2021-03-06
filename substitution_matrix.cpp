#include "substitution_matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

substitution_matrix::substitution_matrix(std::string file, float scale_factor) : scale_factor(scale_factor) {
	for(int i = 0; i < 256; i++) {
		row_index[i] = -1;
		col_index[i] = -1;
	}
	rows = 0;
	cols = 0;
	int last_col_index = 0;
	current_row_index = 0;

	bool is_symetric = false;
	bool is_size_known = false;

	std::ifstream in(file);
	std::string line;
    while(std::getline(in, line)) {
		if(!is_size_known && rows != 0 && cols != 0) {
			scores = new int*[rows];
			for(int i = 0; i < rows; i++) {
				scores[i] = new int[cols];
				for(int j = 0; j < cols; j++) {
					scores[i][j] = 0;
				}
			}	

			is_size_known = true;
		}

		if(line.length() > 0) {
			if(line.at(0) == '#') {
				continue;
			}

			if(line.substr(0, 6).compare("NUMROW") == 0) {
				rows = atoi(line.substr(7, line.length()).c_str());
			}

			if(line.substr(0, 6).compare("NUMCOL") == 0) {
				cols = atoi(line.substr(7, line.length()).c_str());
			}

			if(line.substr(0, 8).compare("ROWINDEX") == 0) {
				std::string index = line.substr(9, line.length());
				parse_index_row(index);
			}

			if(line.substr(0, 8).compare("COLINDEX") == 0) {
				std::string index = line.substr(9, line.length());
				parse_index_col(index);
			}

			if(line.substr(0, 6).compare("MATRIX") == 0) {
				if(!is_size_known) {
					throw;
				}

				int current_col_index = 0;
				std::string values = line.substr(6, line.length());
				std::stringstream sstr(values);
				float score = 0.0f;
				while (sstr >> score) {
					score *= scale_factor;
					int rounded = (int) ((score > 0.0) ? floor(score + 0.5) : ceil(score - 0.5));
					scores[current_row_index][current_col_index] = rounded;
					current_col_index++;
				}

				if(last_col_index + 1 == current_col_index) {
					is_symetric = true;
					current_col_index = last_col_index;
				}

				current_row_index++;
			}
		}
    }

	if(is_symetric)
		normalize();
}

void substitution_matrix::normalize() {
	for(int i = rows - 1; i >= 0; i--) {
		for(int j = cols - 1; j >= 0; j--) {
			int score = scores[i][j];
			if(score != 0.0f && scores[j][i] == 0.0f) {
				scores[j][i] = score;
			}
		}
	}
}

void substitution_matrix::parse_index_row(std::string index) {
	const char* string = index.c_str();	
	for(unsigned int i = 0; i < index.length(); i++) {
		row_index[(unsigned char) string[i]] = i;
	}
}

void substitution_matrix::parse_index_col(std::string index) {
	const char* string = index.c_str();	
	for(unsigned int i = 0; i < index.length(); i++) {
		col_index[(unsigned char) string[i]] = i;
	}
}

substitution_matrix::~substitution_matrix(void) {	
	for(int i = 0; i < rows; i++) {
		delete scores[i];
	}
	delete scores;
}

void substitution_matrix::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << scores[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	 
}

#include "substitution_matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

substitution_matrix::substitution_matrix(std::string file)
{
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
			scores = new float*[rows];
			for(int i = 0; i < rows; i++) {
				scores[i] = new float[cols];
				for(int j = 0; j < cols; j++) {
					scores[i][j] = 0.0f;
				}
			}	

			is_size_known = true;
		}

		if(line.length() > 0)
		{
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
				float score = 0;
				while (sstr >> score) {
					scores[current_row_index][current_col_index] = score;
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
			float score = scores[i][j];
			if(score != 0.0f && scores[j][i] == 0.0f) {
				scores[j][i] = score;
			}
		}
	}
}

void substitution_matrix::parse_index_row(std::string index) {
	const char* string = index.c_str();	
	for(int i = 0; i < index.length(); i++) {
		row_index.insert(pair<char,int>(string[i], i));
	}
}

void substitution_matrix::parse_index_col(std::string index) {
	const char* string = index.c_str();	
	for(int i = 0; i < index.length(); i++) {
		col_index.insert(pair<char,int>(string[i], i));
	}
}

float substitution_matrix::get_score(char residue1, char residue2) {
	int row = row_index.find(residue1)->second;
	int col = col_index.find(residue2)->second;

	return scores[row][col];
}


substitution_matrix::~substitution_matrix(void) {		
	for(int i = 0; i < rows; i++) {
		delete scores[i];
	}
	delete scores;
}

#pragma once

class cell
{
public:
	cell() : row(-1), col(-1), previous((cell*) 0) {};
	cell(int row, int col) : row(row), col(col), previous((cell*) 0) {};
	cell* previous;
	float score;
	int row;
	int col;
};
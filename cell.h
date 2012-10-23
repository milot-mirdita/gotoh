#pragma once

class cell
{
public:
	cell() : row(-1), col(-1) {};
	cell(int row, int col);
	~cell();
	cell* previous;
	float score;
	int row;
	int col;
};
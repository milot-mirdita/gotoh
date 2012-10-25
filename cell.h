#pragma once

struct cell
{
public:
	cell* previous;
	float score;
	int row;
	int col;
};
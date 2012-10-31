#pragma once

struct cell
{
public:
	cell* previous;
	int score;
	int row;
	int col;
};
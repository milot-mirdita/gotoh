//
//  123DConfigParser.h
//  123D
//
//  Created by Martin Steinegger on 11.11.12.
//  Copyright (c) 2012 -. All rights reserved.
//
#pragma once
#include <string>

class config_123d
{
public:
	config_123d(std::string file, float scale_factor);
	~config_123d(void);
	int** scores;
	int rows;
	int cols;
	static const int LOOP=2;
	static const int HELIX=0;
	static const int SHEET=1;

	float scale_factor;
private:
	int current_row_index;
};

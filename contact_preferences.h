//
//  123DConfigParser.h
//  123D
//
//  Created by Martin Steinegger on 11.11.12.
//  Copyright (c) 2012 -. All rights reserved.
//
#pragma once
#include <string>

class contact_preferences
{
public:
	contact_preferences(std::string helix,std::string sheet,std::string loop, float scale_factor);
	~contact_preferences(void);
	int *** matrix_lookup;
    int rows;
	int cols;
    static const int LOOP=2;
    static const int HELIX=0;
    static const int SHEET=1;
private:
	float scale_factor;
	int current_row_index;
	int** h_scores;
	int** l_scores;
	int** s_scores;    
};

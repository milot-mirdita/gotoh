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
	contact_preferences(std::string helix,std::string sheet,std::string loop);
	~contact_preferences(void);
    int** h_scores;
    int** l_scores;
    int** s_scores;
    int rows;
	int cols;
    static const int LOOP=2;
    static const int HELIX=0;
    static const int SHEET=1;
private:
	int current_row_index;
    
    
};

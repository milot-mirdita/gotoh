//
//  123DConfigParser.cpp
//  123D
//
//  Created by Martin Steinegger on 11.11.12.
//  Copyright (c) 2012 -. All rights reserved.
//
#include "config_123d.h"
#include <iostream>
#include <fstream>
#include <sstream>

//
//-WMqieslg       # vom Standard abweichende Reihenfolge
//
//#    L(oop)  H(elix)  S(heet)
//
//-Wm
//11.70    10.57     7.74         # Sequenz
//6.05     2.00     6.63         # Gap insertion
//2.37     5.04     1.66         # Gap extention
//0.06     4.15     0.06         # Sec.Str.Pref.
//0.03     1.81     0.05         # local CCP
//1.25     1.24     6.44         # global CCP



config_123d::~config_123d(void) {		
	for(int i = 0; i < rows; i++) {
		delete scores[i];
	}
	delete scores;
}


config_123d::config_123d(std::string file)
{

	current_row_index = 0;
	

	std::ifstream in(file.c_str());
	std::string line;
	rows = 6;
	cols = 3;
	scores = new float*[rows];
	for(int i = 0; i < rows; i++) {
		scores[i] = new float[cols];
		for(int j = 0; j < cols; j++) {
			scores[i][j] = 0.0f;
		}
	}	
	
	int row=0;
	while(std::getline(in, line)) {

		if(line.length() > 0)
		{
			if(line.at(0) == '#'||line.at(0) == '-') {
				continue;
			}
			
			float loop;
			float helix;
			float sheet;
			
			std::stringstream into;
			into << line;
			into >> loop >> helix >> sheet;
			scores[row][LOOP]=loop;
			scores[row][HELIX]=helix;
			scores[row][SHEET]=sheet;
			row++;
			//std::cout << loop <<"  "<< helix <<"  "<< sheet <<"  ";			
		}
	}
	
}
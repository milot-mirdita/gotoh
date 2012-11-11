//
//  123DConfigParser.cpp
//  123D
//
//  Created by Martin Steinegger on 11.11.12.
//  Copyright (c) 2012 -. All rights reserved.
//
#include "contact_preferences.h"
#include "util.h"
#include "amino_acid_lookup.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


//        0     1     2     3     4     5     6     7     8     9    10    11    12    13 
//ALA   -20     4    -8   -65   -91   -97   -96   -96   -96   -96   -96   -96   -96   -96 
//CYS   198    91    27   -25   -70   -53   -92   -72   -82   -77   -79   -78   -79   -78 
//ASP   -44    13    50    84    97    63   101    82    91    86    89    87    88    88 
//GLU   -89   -43    13    39    90   108   144   126   135   130   132   131   132   131 
//PHE    67   -13   -44   -23    12    21    52    36    44    40    42    41    41    41 
//GLY    82   109    87    51     6     0   -20   -10   -15   -12   -13   -13   -13   -13 
//HIS    12    -5   -13    21    29    74    29    51    40    45    43    44    43    44 
//ILE    78     5   -34   -40   -32   -35   -30   -32   -31   -31   -31   -31   -31   -31 
//LYS   -56   -45    16    77   158   222   320   271   295   283   289   286   287   287 
//LEU    40   -36   -65   -48   -36    -5    -8    -6    -7    -6    -7    -6    -7    -6 
//MET    26   -26   -61   -40   -35   -22   -13   -17   -15   -16   -15   -16   -15   -16 
//ASN    -4    30    31    50    51    46    20    33    26    29    28    28    28    28 
//PRO    44    88    87    74    58    18    67    42    54    48    51    50    50    50 
//GLN   -56   -52     1    39    55   112   113   112   112   112   112   112   112   112 
//ARG   -38   -54   -13    31    80   149   159   154   156   155   155   155   155   155 
//SER    -4    37    53    28    15     0   -25   -12   -18   -15   -17   -16   -16   -16 
//THR    25    42    46    24    21     0    -4    -2    -3    -2    -2    -2    -2    -2 
//VAL    93    42     1   -30   -38   -62   -56   -59   -57   -58   -57   -58   -57   -58 
//TRP    45   -26   -40   -33    14    22    74    48    61    54    57    56    56    56 
//TYR    58    -3   -35   -13     4    42    66    54    60    57    58    57    58    57 
//UNK    22     7     4    10    19    30    40    35    37    36    36    36    36    36 




contact_preferences::~contact_preferences(void) {		
	for(int i = 0; i < rows; i++) {
		delete h_scores[i];
        delete s_scores[i];
        delete l_scores[i];

	}
	delete h_scores;
    delete s_scores;
	delete l_scores;

}


contact_preferences::contact_preferences(std::string helix,std::string sheet,std::string loop)
{

	current_row_index = 0;
    std::string files_to_process[]={helix,sheet,loop};
    int *** matrix_lookup = new int**[3];
    rows = 26;

    h_scores = new int*[rows];
    s_scores = new int*[rows];
    l_scores = new int*[rows];
    matrix_lookup[0]=h_scores;
    matrix_lookup[1]=s_scores;
    matrix_lookup[2]=l_scores;

    for(size_t i = 0 ; i < 3;i++){
        int ** scores = matrix_lookup[i];
        std::string file=files_to_process[i];
        std::ifstream in(file.c_str());
        std::string line;

        // first line
        std::getline(in, line);
        int int_last_index=0;
        std::vector<std::string> first_line= split(line,' ');
        std::string last_index_string=first_line.at(first_line.size()-1);
        std::stringstream parse;
        parse << last_index_string;
        parse >> int_last_index;
        cols = int_last_index+1;
        
        
        for(int i = 0; i < rows; i++) {
            scores[i] = new int[cols];
            for(int j = 0; j < cols; j++) {
                scores[i][j] = 0.0;
            }
        }	
        while(std::getline(in, line)) {
            
            if(line.length() > 0)
            {
                if(line.at(0) == '#'||line.at(0) == '-') {
                    continue;
                }
                std::stringstream into;
                into << line;
                std::string aa_name;
                into >> aa_name;
                int aa_index=amino_acid_lookup::find_one_letter_code(aa_name)-65;
                int value;
                for(int col = 0; col < cols; col++) {
                    into >> value;
                    scores[aa_index][col]=value;
                }
            }
        }
    }
    
}
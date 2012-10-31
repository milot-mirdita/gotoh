//
//  util.h
//  AlgoUmMilotZuZerstoeren
//
//  Created by Martin Steinegger on 23.10.12.
//  Copyright (c) 2012 -. All rights reserved.
//

#ifndef AlgoUmMilotZuZerstoeren_util_h
#define AlgoUmMilotZuZerstoeren_util_h

#include <vector>
#include <string>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif

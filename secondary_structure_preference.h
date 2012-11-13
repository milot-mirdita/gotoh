#pragma once
#include <string>

class secondary_structure_preference
{
public:
	secondary_structure_preference(std::string file, float scale_factor);
	~secondary_structure_preference(void);

	inline int get_score(int secondary_structure, unsigned char residue) {
		return scores[secondary_structure][residue];
	}

protected:
	int scores[3][26];
	float scale_factor;
};


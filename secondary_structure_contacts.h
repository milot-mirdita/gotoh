#pragma once
#include <vector>
#include <string>

struct sscc_entries {
	//unsigned char* residue;
	int length;
	unsigned char* secondary_structure;
	int* global_contacts;
	int* local_contacts;
};

class secondary_structure_contacts
{
protected:
	int max_length;
public:
	secondary_structure_contacts(int max_length);
	~secondary_structure_contacts(void);
	void parse_file(std::string file);
	sscc_entries entries;
};


#pragma once
class gap_costs
{
public:
	gap_costs(int gap_open, int gap_extend);
	int gap_cost(int k);
	int gap_open;
	int gap_extend;
};


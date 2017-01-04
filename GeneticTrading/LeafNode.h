#pragma once

#include "Node.h"
#include <string>
#include <cstdlib>
#include <ctime>

class LeafNode :
	public Node
{
private:
	shared_ptr<Indicator> indicator;
	bool greater;
	uint8_t value;
public:
	LeafNode(vector<shared_ptr<Indicator>> & indicators);
	~LeafNode();

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
};

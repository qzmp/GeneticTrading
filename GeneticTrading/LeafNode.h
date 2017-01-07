#pragma once

#include "Node.h"
#include <string>
#include <cstdlib>
#include <ctime>

class InternalNode;

class LeafNode :
	public Node
{
private:
	shared_ptr<Indicator> indicator;
	bool greater;
	uint8_t value;

	void randomizeValue();
	void randomizeIndicator();

public:
	LeafNode(Tree * ownerTree);
	~LeafNode();

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	void mutate(InternalNode & parent, bool isLeft, int currentPos);

	bool isLeaf();
};


#pragma once

#include "Node.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class InternalNode;

class LeafNode :
	public Node
{
private:
	shared_ptr<Indicator> indicator;
	bool greater;
	uint8_t value;

	void randomizeValue();
	void randomizeIndicator(Tree *ownerTree);

public:
	LeafNode(Tree *ownerTree);
	LeafNode(const LeafNode &other);
	Node* clone();
	~LeafNode();

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	void mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree);

	bool isLeaf();
};


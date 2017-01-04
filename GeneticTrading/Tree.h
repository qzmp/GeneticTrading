#pragma once

#include "Indicator.h"
#include "Node.h"
#include "InternalNode.h"
#include <list>


class Tree
{
private:
	shared_ptr<Node> rootNode;
public:
	Tree();
	~Tree();

	void generateRandom(vector<shared_ptr<Indicator>> & indicators, int treeHeight);
	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
};
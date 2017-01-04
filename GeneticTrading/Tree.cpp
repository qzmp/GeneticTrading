#include "Tree.h"



Tree::Tree()
{
}


Tree::~Tree()
{
}

void Tree::generateRandom(vector<shared_ptr<Indicator>> & indicators, int treeHeight)
{
	rootNode = shared_ptr<Node>(new InternalNode(indicators, 1, treeHeight));
}

bool Tree::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return rootNode->isActive(currentPrice, indicatorValues);
}
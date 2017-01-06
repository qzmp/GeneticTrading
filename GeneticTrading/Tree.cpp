#include "Tree.h"


Tree::Tree(vector<shared_ptr<Indicator>> * indicators, MutationChances * mutationChances, int maxTreeHeight) : indicators(indicators), mutationChances(mutationChances), maxTreeHeight(maxTreeHeight)
{
}

Tree::~Tree()
{
}

void Tree::generateRandom()
{
	rootNode = shared_ptr<InternalNode>(new InternalNode(1, this));
}

bool Tree::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return rootNode->isActive(currentPrice, indicatorValues);
}

void Tree::mutate()
{
	rootNode->mutate(*rootNode, false, 0); // to be changed
}

MutationChances * Tree::getMutationChances()
{
	return mutationChances;
}

vector<shared_ptr<Indicator>>* Tree::getIndicators()
{
	return indicators;
}

int Tree::getMaxHeight()
{
	return maxTreeHeight;
}

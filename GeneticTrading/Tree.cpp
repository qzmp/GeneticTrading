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
	if (rand() < mutationChances->getCutChance())
	{
		bool cutLeft = rand() % 2 == 0;
		if (cutLeft)
		{
			if (!rootNode->getRight()->isLeaf())
			{
				rootNode = dynamic_pointer_cast<InternalNode>(rootNode->getRight());
			}
			else if (!rootNode->getLeft()->isLeaf())
			{
				rootNode = dynamic_pointer_cast<InternalNode>(rootNode->getLeft());
			}
		}
		else
		{
			if (!rootNode->getLeft()->isLeaf())
			{
				rootNode = dynamic_pointer_cast<InternalNode>(rootNode->getLeft());
			}
			else if (!rootNode->getRight()->isLeaf())
			{
				rootNode = dynamic_pointer_cast<InternalNode>(rootNode->getRight());
			}
		}
	}
	rootNode->mutate(*rootNode, false, 0);
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

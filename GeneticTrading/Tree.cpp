#include "Tree.h"


Tree::Tree()
{
}

Tree::Tree(IndicatorHolder * indicators, MutationChances * mutationChances, int maxTreeHeight) : indicators(indicators), mutationChances(mutationChances), maxTreeHeight(maxTreeHeight)
{
}

Tree::Tree(const Tree & other)
	: rootNode(unique_ptr<InternalNode>(new InternalNode(*other.rootNode))), indicators(other.indicators), mutationChances(other.mutationChances), maxTreeHeight(other.maxTreeHeight)
{
}

Tree::~Tree()
{
	//cout << "tree destroyed" << endl;
}

void Tree::generateRandom()
{
	rootNode = unique_ptr<InternalNode>(new InternalNode(1, this));
}

bool Tree::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return rootNode->isActive(currentPrice, indicatorValues);
}

void Tree::mutate()
{
	if (rand() / double(RAND_MAX) < mutationChances->getCutChance())
	{
		bool cutLeft = rand() % 2 == 0;
		if (cutLeft)
		{
			if (!rootNode->isRightLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseRight());
			}
			else if (!rootNode->isLeftLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseLeft());
			}
		}
		else
		{
			if (!rootNode->isLeftLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseLeft());
			}
			else if (!rootNode->isRightLeaf())
			{
				rootNode.reset((InternalNode*)rootNode->releaseRight());
			}
		}
	}
	rootNode->mutate(*rootNode, false, 0, this);
}

MutationChances * Tree::getMutationChances()
{
	return mutationChances;
}

IndicatorHolder* Tree::getIndicators()
{
	return indicators;
}

int Tree::getMaxHeight()
{
	return maxTreeHeight;
}

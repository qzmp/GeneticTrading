#include "LeafNode.h"
#include "InternalNode.h"
#include "Tree.h"


void LeafNode::randomizeValue()
{
	value = rand() % numeric_limits<uint8_t>::max();
}

void LeafNode::randomizeIndicator()
{
	int randomIndicatorIndex = rand() % ownerTree->getIndicators()->size();
	indicator = ownerTree->getIndicators()->operator[](randomIndicatorIndex);
}

LeafNode::LeafNode(Tree * ownerTree) : Node(ownerTree)
{
	randomizeIndicator();
	greater = rand() % 2 == 0;
	randomizeValue();
}

LeafNode::~LeafNode()
{
}

bool LeafNode::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return indicator->isActive(greater, value, currentPrice, indicatorValues[indicator]);
}

void LeafNode::mutate(InternalNode & parent, bool isLeft, int currentPos)
{
	if (rand() < ownerTree->getMutationChances()->getValueChangeChance())
	{
		randomizeValue();
	}
	if (rand() < ownerTree->getMutationChances()->getComparatorChangeChance())
	{
		greater != greater;
	}
	if (rand() < ownerTree->getMutationChances()->getIndicatorChangeChance())
	{
		randomizeIndicator();
	}
	if (currentPos < ownerTree->getMaxHeight() && rand() < ownerTree->getMutationChances()->getSplitChance())
	{
		if (isLeft)
		{
			parent.setLeft(shared_ptr<Node>(new InternalNode(currentPos, ownerTree, shared_ptr<Node>(this))));
		}
		else
		{
			parent.setRight(shared_ptr<Node>(new InternalNode(currentPos, ownerTree, shared_ptr<Node>(this))));
		}
	}
}

bool LeafNode::isLeaf()
{
	return true;
}

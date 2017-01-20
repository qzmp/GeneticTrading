#include "LeafNode.h"
#include "InternalNode.h"
#include "Tree.h"


void LeafNode::randomizeValue()
{
	value = rand() % numeric_limits<uint8_t>::max();
}

void LeafNode::randomizeIndicator(Tree *ownerTree)
{
	int randomIndicatorIndex = rand() % ownerTree->getIndicators()->size();
	indicator = ownerTree->getIndicators()->operator[](randomIndicatorIndex);
}

LeafNode::LeafNode(Tree *ownerTree)
{
	randomizeIndicator(ownerTree);
	greater = rand() % 2 == 0;
	randomizeValue();
}

LeafNode::LeafNode(const LeafNode & other) : indicator(other.indicator), greater(other.greater), value(other.value)
{
}

Node * LeafNode::clone()
{
	return new LeafNode(*this);
}

LeafNode::~LeafNode()
{
	//cout << "leaf destructed" << endl;;
}

bool LeafNode::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return indicator->isActive(greater, value, currentPrice, indicatorValues[indicator]);
}

void LeafNode::mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree)
{
	if (rand() < ownerTree->getMutationChances()->getValueChangeChance())
	{
		randomizeValue();
	}
	if (rand() < ownerTree->getMutationChances()->getComparatorChangeChance())
	{
		greater = !greater;
	}
	if (rand() < ownerTree->getMutationChances()->getIndicatorChangeChance())
	{
		randomizeIndicator(ownerTree);
	}
	if (currentPos < ownerTree->getMaxHeight() && rand() < ownerTree->getMutationChances()->getSplitChance())
	{
		if (isLeft)
		{
			parent.splitLeft(currentPos, ownerTree);		
		}
		else
		{
			parent.splitRight(currentPos, ownerTree);
		}
	}
}

bool LeafNode::isLeaf()
{
	return true;
}

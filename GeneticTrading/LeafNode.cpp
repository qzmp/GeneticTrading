#include "LeafNode.h"
#include "InternalNode.h"
#include "Tree.h"

void LeafNode::randomizeAll(IndicatorHolder * indicators)
{
	indicator = indicators->getRandom();
	if (indicator->isTrendIndicator())
	{
		if (rand() % (indicators->getTrendIndicatorCount() + 1) == 0)
			currentPrice = true;
		else
		{
			currentPrice = false;
			secondIndicator = indicators->getRandomTrendIndicator();
		}
		doubleIndicators = true;
	}
	else
	{
		randomizeValue();
		doubleIndicators = false;
	}
}

void LeafNode::randomizeValue()
{
	value = rand() % numeric_limits<uint8_t>::max();
}

LeafNode::LeafNode(Tree * ownerTree)
{
	greater = rand() % 2 == 0;
	randomizeAll(ownerTree->getIndicators());
}

LeafNode::LeafNode(const LeafNode & other) 
	: indicator(other.indicator), greater(other.greater), secondIndicator(other.secondIndicator), value(other.value), 
	currentPrice(other.currentPrice), doubleIndicators(other.doubleIndicators)
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
	if (doubleIndicators)
	{
		if(currentPrice)
			return greater ? indicatorValues[indicator] > indicatorValues[secondIndicator] : indicatorValues[indicator] < indicatorValues[secondIndicator];
		else
			return greater ? indicatorValues[indicator] > currentPrice : indicatorValues[indicator] < currentPrice;
	}
	else
		return greater ? indicatorValues[indicator] > indicator->normalizeValue(value) : indicatorValues[indicator] < indicator->normalizeValue(value);
}

void LeafNode::mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree)
{

	if (rand() / double(RAND_MAX) < ownerTree->getMutationChances()->getIndicatorChangeChance())
	{
		randomizeAll(ownerTree->getIndicators());
	}

	if (currentPos < ownerTree->getMaxHeight() && rand() / double(RAND_MAX) < ownerTree->getMutationChances()->getSplitChance())
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

int LeafNode::getSize()
{
	return 1;
}

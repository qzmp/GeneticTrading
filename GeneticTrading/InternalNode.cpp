#include "InternalNode.h"



int InternalNode::generateRandomBranch(vector<shared_ptr<Indicator>> & indicators, bool leftBranch, int currentSize, int maxSize)
{
	shared_ptr<Node> randomNode;
	if (rand() % 2 == 0)
	{
		randomNode = shared_ptr<Node>(new InternalNode(indicators, currentSize + 1, maxSize));
	}
	else
	{
		randomNode = shared_ptr<Node>(new LeafNode(indicators));
	}

	if (leftBranch)
	{
		left = randomNode;
	}
	else
	{
		right = randomNode;
	}
	return 0;
}

InternalNode::InternalNode(vector<shared_ptr<Indicator>>& indicators, int currentSize, int maxSize)
{
	this->isAndOperator = rand() % 2 == 0;
	generateRandomBranches(indicators, currentSize, maxSize);
}

InternalNode::InternalNode(bool isAndOperator)
{
	this->isAndOperator = isAndOperator;
}


InternalNode::~InternalNode()
{
}

shared_ptr<Node> InternalNode::getLeft()
{
	return left;
}

shared_ptr<Node> InternalNode::getRight()
{
	return right;
}

bool InternalNode::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	if (isAndOperator)
		return left->isActive(currentPrice, indicatorValues) && right->isActive(currentPrice, indicatorValues);
	else
		return left->isActive(currentPrice, indicatorValues) || right->isActive(currentPrice, indicatorValues);
}

void InternalNode::changeOperator()
{
	this->isAndOperator = !isAndOperator;
}

int InternalNode::generateRandomBranches(vector<shared_ptr<Indicator>> & indicators, int currentSize, int maxSize)
{
	if (currentSize + 1 == maxSize)
	{
		left = shared_ptr<Node>(new LeafNode(indicators));
		right = shared_ptr<Node>(new LeafNode(indicators));
	}
	else
	{
		generateRandomBranch(indicators, true, currentSize, maxSize);
		generateRandomBranch(indicators, false, currentSize, maxSize);
	}
	return 0;
}

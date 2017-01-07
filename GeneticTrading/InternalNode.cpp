#include "InternalNode.h"
#include "Tree.h"



int InternalNode::generateRandomBranch(bool leftBranch, int currentSize)
{
	shared_ptr<Node> randomNode;
	if (rand() % 2 == 0)
	{
		randomNode = shared_ptr<Node>(new InternalNode(currentSize + 1, this->ownerTree));
	}
	else
	{
		randomNode = shared_ptr<Node>(new LeafNode(this->ownerTree));
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

InternalNode::InternalNode(int currentSize, Tree * ownerTree) : Node(ownerTree)
{
	this->isAndOperator = rand() % 2 == 0;
	generateRandomBranches(currentSize);
}

InternalNode::InternalNode(int currentSize, Tree * ownerTree, shared_ptr<Node> subtree) : Node(ownerTree)
{
	this->isAndOperator = rand() % 2 == 0;
	if (rand() % 2 == 0)
	{
		this->left = subtree;
		generateRandomBranch(false, currentSize);
	}
	else
	{
		this->right = subtree;
		generateRandomBranch(true, currentSize);
	}
}

InternalNode::InternalNode(bool isAndOperator, Tree * ownerTree) : Node(ownerTree)
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

void InternalNode::setLeft(shared_ptr<Node> & node)
{
	left = node;
}

void InternalNode::setRight(shared_ptr<Node>& node)
{
	right = node;
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

int InternalNode::generateRandomBranches(int currentSize)
{
	if (currentSize + 1 == ownerTree->getMaxHeight())
	{
		left = shared_ptr<Node>(new LeafNode(ownerTree));
		right = shared_ptr<Node>(new LeafNode(ownerTree));
	}
	else
	{
		generateRandomBranch(true, currentSize);
		generateRandomBranch(false, currentSize);
	}
	return 0;
}


void InternalNode::mutate(InternalNode & parent, bool isLeft, int currentPos)
{
	if (rand() < ownerTree->getMutationChances()->getOperatorChangeChance())
	{
		this->isAndOperator = !this->isAndOperator;
	}

	if (currentPos != 0 && rand() < ownerTree->getMutationChances()->getCutChance())
	{
		bool cutLeft = rand() % 2 == 0;
		if (cutLeft)
		{
			if (isLeft)
			{
				parent.setLeft(this->getRight());
			}
			else
			{
				parent.setRight(this->getLeft());
			}
		}
		else
		{
			if (isLeft)
			{
				parent.setLeft(this->getLeft());
			}
			else
			{
				parent.setRight(this->getRight());
			}
		}
	}
	if (rand() < ownerTree->getMutationChances()->getSwapChance())
	{
		shared_ptr<Node> & temp = this->left;
		this->left = this->right;
		this->right = temp;
	}

	left->mutate(*this, true, currentPos + 1);
	right->mutate(*this, false, currentPos + 1);
}

bool InternalNode::isLeaf()
{
	return false;
}


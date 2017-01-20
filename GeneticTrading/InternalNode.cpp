#include "InternalNode.h"
#include "Tree.h"



int InternalNode::generateRandomBranch(bool leftBranch, int currentSize, Tree *ownerTree)
{
	unique_ptr<Node> randomNode;
	if (rand() % 2 == 0)
	{
		randomNode = unique_ptr<Node>(new InternalNode(currentSize + 1, ownerTree));
	}
	else
	{
		randomNode = unique_ptr<Node>(new LeafNode(ownerTree));
	}

	if (leftBranch)
	{
		left = move(randomNode);
	}
	else
	{
		right = move(randomNode);
	}
	return 0;
}

InternalNode::InternalNode(int currentSize, Tree *ownerTree)
{
	this->isAndOperator = rand() % 2 == 0;
	generateRandomBranches(currentSize, ownerTree);
}

InternalNode::InternalNode(int currentSize, Node * subtree, Tree *ownerTree)
{
	this->isAndOperator = rand() % 2 == 0;
	if (rand() % 2 == 0)
	{
		this->left.reset(subtree);
		generateRandomBranch(false, currentSize, ownerTree);
	}
	else
	{
		this->right.reset(subtree);
		generateRandomBranch(true, currentSize, ownerTree);
	}
}

InternalNode::InternalNode(bool isAndOperator)
{
	this->isAndOperator = isAndOperator;
}

InternalNode::InternalNode(const InternalNode & other) : isAndOperator(other.isAndOperator)
{
	left = unique_ptr<Node>(other.left->clone());
	right = unique_ptr<Node>(other.right->clone());
}

Node * InternalNode::clone()
{
	return new InternalNode(*this);
}


InternalNode::~InternalNode()
{
	//cout << "internal destroyed" << endl;
}

Node* InternalNode::releaseLeft()
{
	return left.release();
}

Node* InternalNode::releaseRight()
{
	return right.release();
}

void InternalNode::setLeft(Node * node)
{
	left = unique_ptr<Node>(node);
}

void InternalNode::setRight(Node * node)
{
	right = unique_ptr<Node>(node);
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

int InternalNode::generateRandomBranches(int currentSize, Tree *ownerTree)
{
	if (currentSize + 1 == ownerTree->getMaxHeight())
	{
		left = unique_ptr<Node>(new LeafNode(ownerTree));
		right = unique_ptr<Node>(new LeafNode(ownerTree));
	}
	else
	{
		generateRandomBranch(true, currentSize, ownerTree);
		generateRandomBranch(false, currentSize, ownerTree);
	}
	return 0;
}


void InternalNode::mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree)
{
	if (currentPos != 0 && rand() < ownerTree->getMutationChances()->getCutChance())
	{
		bool cutLeft = rand() % 2 == 0;
		if (cutLeft)
		{
			if (isLeft)
			{
				parent.setLeft(this->releaseRight());
			}
			else
			{
				parent.setRight(this->releaseLeft());
			}
		}
		else
		{
			if (isLeft)
			{
				parent.setLeft(this->releaseLeft());
			}
			else
			{
				parent.setRight(this->releaseRight());
			}
		}
		return;
	}
	if (rand() < ownerTree->getMutationChances()->getOperatorChangeChance())
	{
		this->isAndOperator = !this->isAndOperator;
	}
	if (rand() < ownerTree->getMutationChances()->getSwapChance())
	{
		this->left.swap(this->right);
	}

	left->mutate(*this, true, currentPos + 1, ownerTree);
	right->mutate(*this, false, currentPos + 1, ownerTree);
}

bool InternalNode::isLeaf()
{
	return false;
}

bool InternalNode::isLeftLeaf()
{
	return left->isLeaf();
}

bool InternalNode::isRightLeaf()
{
	return right->isLeaf();
}

void InternalNode::splitLeft(int currentSize, Tree *ownerTree)
{
	left = make_unique<InternalNode>(currentSize, left.release(), ownerTree);
}

void InternalNode::splitRight(int currentSize, Tree * ownerTree)
{
	right = make_unique<InternalNode>(currentSize, right.release(), ownerTree);
}


#include "InternalNode.h"
#include "Tree.h"



int InternalNode::generateRandomBranch(bool leftBranch, int currentSize, Tree *ownerTree)
{
	unique_ptr<Node> randomNode;
	if (rand() % 2 == 0)
	{
		randomNode = make_unique<InternalNode>(currentSize + 1, ownerTree);
	}
	else
	{
		randomNode = make_unique<LeafNode>(ownerTree);
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
	left = other.left->clone();
	right = other.right->clone();
}

unique_ptr<Node> InternalNode::clone()
{
	return make_unique<InternalNode>(*this);
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

void InternalNode::setLeft(unique_ptr<Node> node)
{
	left.swap(node);
}

void InternalNode::setRight(unique_ptr<Node> node)
{
	right.swap(node);
}

unique_ptr<Node> InternalNode::getLeftCopy()
{
	return left->clone();
}

unique_ptr<Node> InternalNode::getRightCopy()
{
	return right->clone();
}

bool InternalNode::isActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues) const
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
	if (currentSize + 1 >= ownerTree->getMaxHeight())
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
	if (currentPos != 0 && rand() / double(RAND_MAX) < ownerTree->getMutationChances()->getCutChance())
	{
		if (isLeft)
		{
			parent.setLeft(move(make_unique<LeafNode>(ownerTree)));
		}
		else
		{
			parent.setRight(move(make_unique<LeafNode>(ownerTree)));
		}
		/*
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
		*/
		return;
	}
	if (rand() / double(RAND_MAX) < ownerTree->getMutationChances()->getCycleChance())
	{
		this->isAndOperator = !this->isAndOperator;
	}
	if (rand() / double(RAND_MAX) < ownerTree->getMutationChances()->getSwapChance())
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

int InternalNode::getSize()
{
	return 1 + left->getSize() + right->getSize();
}

void InternalNode::writeLatex(stringstream & ss)
{
	isAndOperator ? ss << "[.AND" : ss << "[.OR";
	ss << endl;

	ss << "[";
	left->writeLatex(ss);
	ss << " ";
	right->writeLatex(ss);
	ss << " ]";
	ss << " ]" << endl;
}

void InternalNode::getRandomPath(list<bool>& path)
{
	if (rand() % 2 == 0)
	{
		path.push_back(true);
		this->left->getRandomPath(path);
	}
	else
	{
		path.push_back(false);
		this->right->getRandomPath(path);
	}
}

unique_ptr<Node> InternalNode::getNodeFromPath(list<bool>::iterator& pathIterator, int index)
{
	if (index == 0)
	{
		return *pathIterator ? unique_ptr<Node>(left->clone()) : unique_ptr<Node>(right->clone());
	}
	else
	{
		return *pathIterator ? left->getNodeFromPath(++pathIterator, --index) : right->getNodeFromPath(++pathIterator, --index);
	}
}

void InternalNode::swapSubtree(list<bool>::iterator & pathIterator, int index, unique_ptr<Node>& subtree)
{
	if (index == 0)
	{
		*pathIterator ? left.swap(subtree) : right.swap(subtree);
	}
	else
	{
		*pathIterator ? left->swapSubtree(++pathIterator, --index, subtree) : right->swapSubtree(++pathIterator, --index, subtree);
	}
}


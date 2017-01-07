#pragma once

#include "Node.h"
#include "LeafNode.h"
#include <memory>
#include <ctime>

using namespace std;

class InternalNode : public Node
{
private:
	shared_ptr<Node> left;
	shared_ptr<Node> right;

	bool isAndOperator;

	int generateRandomBranch(bool leftBranch, int currentSize);
public:
	InternalNode(int currentSize, Tree * ownerTree);
	InternalNode(int currentSize, Tree * ownerTree, shared_ptr<Node> subtree);
	InternalNode(bool isAndOperator, Tree * ownerTree);
	~InternalNode();

	shared_ptr<Node> getLeft();
	shared_ptr<Node> getRight();
	void setLeft(shared_ptr<Node> & node);
	void setRight(shared_ptr<Node> & node);

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	void changeOperator();

	int generateRandomBranches(int currentSize);

	void mutate(InternalNode & parent, bool isLeft, int currentPos);

	bool isLeaf();
};


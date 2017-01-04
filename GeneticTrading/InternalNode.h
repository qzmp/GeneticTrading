#pragma once

#include "Node.h"
#include "LeafNode.h"
#include <memory>

using namespace std;

class InternalNode : public Node
{
private:
	shared_ptr<Node> left;
	shared_ptr<Node> right;

	bool isAndOperator;

	int generateRandomBranch(vector<shared_ptr<Indicator>> & indicators, bool leftBranch, int currentSize, int maxSize);
public:
	InternalNode(vector<shared_ptr<Indicator>> & indicators, int currentSize, int maxSize);
	InternalNode(bool isAndOperator);
	~InternalNode();

	shared_ptr<Node> getLeft();
	shared_ptr<Node> getRight();

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	void changeOperator();

	int generateRandomBranches(vector<shared_ptr<Indicator>> & indicators, int currentSize, int maxSize);
};


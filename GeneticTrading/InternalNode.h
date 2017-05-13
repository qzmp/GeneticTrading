#pragma once

#include "Node.h"
#include "LeafNode.h"
#include <memory>
#include <ctime>

using namespace std;

class InternalNode : public Node
{
private:
	unique_ptr<Node> left;
	unique_ptr<Node> right;

	bool isAndOperator;

	int generateRandomBranch(bool leftBranch, int currentSize, Tree *ownerTree);
public:
	InternalNode(int currentSize, Tree *ownerTree);
	InternalNode(int currentSize, Node * subtree, Tree *ownerTree);
	InternalNode(bool isAndOperator);
	InternalNode(const InternalNode &other);
	Node* clone();
	~InternalNode();

	Node* releaseLeft();
	Node* releaseRight();
	void setLeft(Node * node);
	void setRight(Node * node);

	Node* getLeftCopy();
	Node* getRightCopy();

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	void changeOperator();

	int generateRandomBranches(int currentSize, Tree *ownerTree);

	void mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree);

	bool isLeaf();
	bool isLeftLeaf();
	bool isRightLeaf();

	void splitLeft(int currentSize, Tree *ownerTree);
	void splitRight(int currentSize, Tree *ownerTree);

	int getSize();

	void writeLatex(stringstream& ss);
};


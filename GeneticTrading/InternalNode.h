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
	unique_ptr<Node> clone();
	~InternalNode();

	Node* releaseLeft();
	Node* releaseRight();
	void setLeft(unique_ptr<Node> node);
	void setRight(unique_ptr<Node> node);

	unique_ptr<Node> getLeftCopy();
	unique_ptr<Node> getRightCopy();

	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) const;
	void changeOperator();

	int generateRandomBranches(int currentSize, Tree *ownerTree);

	void mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree);

	bool isLeaf();
	bool isLeftLeaf();
	bool isRightLeaf();

	void splitLeft(int currentSize, Tree *ownerTree);
	void splitRight(int currentSize, Tree *ownerTree);

	int getSize();
	int getHeight();

	void writeLatex(stringstream& ss);

	void getRandomPath(list<bool>& path);
	unique_ptr<Node> getNodeFromPath(list<bool>::iterator& pathIterator, int index);
	void swapSubtree(list<bool>::iterator& pathIterator, int index, unique_ptr<Node>& subtree);
};


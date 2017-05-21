#pragma once

#include "Node.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class InternalNode;

class LeafNode :
	public Node
{
private:
	shared_ptr<Indicator> indicator;
	bool greater;
	
	shared_ptr<Indicator> secondIndicator;
	uint8_t value;

	bool currentPrice;

	bool doubleIndicators;
	
	void randomizeAll(IndicatorHolder * indicators);
	void randomizeValue();

public:
	LeafNode(Tree * ownerTree);
	LeafNode(const LeafNode &other);
	unique_ptr<Node> clone();
	~LeafNode();


	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	void mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree);

	bool isLeaf();

	int getSize();

	void writeLatex(stringstream& ss);
	
	void getRandomPath(list<bool>& path);
	unique_ptr<Node> getNodeFromPath(list<bool>::iterator& path, int index);
	void swapSubtree(list<bool>::iterator& pathIterator, int index, unique_ptr<Node>& subtree);
};


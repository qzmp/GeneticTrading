#pragma once

#include <memory>
#include "Indicator.h"
#include "MutationChances.h"
#include <vector>
#include <map>

using namespace std;

class Tree;
class InternalNode;

class Node
{
protected:
	Tree * ownerTree;

public:
	Node(Tree * ownerTree);
	~Node();

	virtual bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) = 0;

	virtual void mutate(InternalNode & parent, bool isLeft, int currentPos) = 0;
};


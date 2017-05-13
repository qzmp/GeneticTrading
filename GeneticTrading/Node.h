#pragma once

#include <memory>
#include "Indicator.h"
#include "IndicatorHolder.h"
#include "MutationChances.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Tree;
class InternalNode;

class Node
{
public:
	Node();
	virtual ~Node();

	virtual Node* clone() = 0;

	virtual bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) = 0;

	virtual void mutate(InternalNode & parent, bool isLeft, int currentPos, Tree *ownerTree) = 0;

	virtual bool isLeaf() = 0;
	
	virtual int getSize() = 0;

	virtual void writeLatex(stringstream& ss) = 0;
};


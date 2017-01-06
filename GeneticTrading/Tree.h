#pragma once

#include "Indicator.h"
#include "InternalNode.h"
#include <list>


class Tree
{
private:
	shared_ptr<InternalNode> rootNode;

	vector<shared_ptr<Indicator>> * indicators;
	MutationChances * mutationChances;
	int maxTreeHeight;

public:
	Tree(vector<shared_ptr<Indicator>> * indicators, MutationChances * mutationChances, int maxTreeHeight);
	~Tree();

	void generateRandom();
	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	
	void mutate();

	MutationChances * getMutationChances();
	vector<shared_ptr<Indicator>> * getIndicators();
	int getMaxHeight();

};
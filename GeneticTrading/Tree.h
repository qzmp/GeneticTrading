#pragma once

#include "Indicator.h"
#include "InternalNode.h"
#include <list>


class Tree
{
private:
	unique_ptr<InternalNode> rootNode;

	vector<shared_ptr<Indicator>> * indicators;
	MutationChances * mutationChances;
	int maxTreeHeight;

public:
	Tree();
	Tree(vector<shared_ptr<Indicator>> * indicators, MutationChances * mutationChances, int maxTreeHeight);
	Tree(const Tree &other);
	~Tree();

	void generateRandom();
	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	
	void mutate();

	MutationChances * getMutationChances();
	vector<shared_ptr<Indicator>> * getIndicators();
	int getMaxHeight();

};
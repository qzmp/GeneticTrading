#pragma once

//#include "IndicatorHolder.h"
#include "InternalNode.h"
#include <list>


class Tree
{
private:
	unique_ptr<InternalNode> rootNode;

	IndicatorHolder * indicators;
	MutationChances * mutationChances;
	int maxTreeHeight;

public:
	Tree();
	Tree(IndicatorHolder * indicators, MutationChances * mutationChances, int maxTreeHeight);
	Tree(const Tree &other);
	~Tree();

	void generateRandom();
	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	
	void mutate();

	MutationChances * getMutationChances();
	IndicatorHolder * getIndicators();
	int getMaxHeight();

	int getSize();

	unique_ptr<Tree> crossLeft(const Tree& other);
	unique_ptr<Tree> crossRight(const Tree& other);

	string drawLatex();

};
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

	list<bool> getRandomPath() const;
	unique_ptr<Node> getNodeFromPath(list<bool>& path, int index) const;
	void swapSubtree(list<bool>& path, int index, unique_ptr<Node>& subtree);

public:
	Tree();
	Tree(IndicatorHolder * indicators, MutationChances * mutationChances, int maxTreeHeight);
	Tree(const Tree &other);
	~Tree();

	void generateRandom();
	bool isActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) const;
	
	void mutate();

	MutationChances * getMutationChances();
	IndicatorHolder * getIndicators();
	int getMaxHeight();

	int getSize();

	unique_ptr<Tree> crossLeft(const Tree& other);
	unique_ptr<Tree> crossRight(const Tree& other);
	pair<unique_ptr<Tree>, unique_ptr<Tree>> cross(const Tree& other);

	string drawLatex();

	shared_ptr<Node> getRandomNode();


};
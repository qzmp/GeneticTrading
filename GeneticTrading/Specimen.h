#pragma once

#include "Tree.h"
#include <iostream>
class Specimen
{
private:
	Tree bullTree;
	Tree bearTree;

public:
	Specimen();
	Specimen(vector<shared_ptr<Indicator>> * indicators, MutationChances * mutationChances, int treeHeight);
	Specimen(Tree bullTree, Tree bearTree);
	Specimen(const Specimen &other);
	~Specimen();

	bool bullActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool bearActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	Specimen cross(Specimen & other);
	void mutate();
};


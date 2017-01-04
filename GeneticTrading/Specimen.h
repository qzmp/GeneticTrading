#pragma once

#include "Tree.h"
class Specimen
{
private:
	Tree bullTree;
	Tree bearTree;

public:
	Specimen(vector<shared_ptr<Indicator>> indicators, int treeHeight);
	~Specimen();

	bool bullActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool bearActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	int cross(Specimen & other);
	int mutate();
};


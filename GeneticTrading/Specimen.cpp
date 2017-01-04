#include "Specimen.h"



Specimen::Specimen(vector<shared_ptr<Indicator>> indicators, int treeHeight)
{
	bullTree.generateRandom(indicators, treeHeight);
	bearTree.generateRandom(indicators, treeHeight);
}


Specimen::~Specimen()
{
}

bool Specimen::bullActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bullTree.isActive(currentPrice, indicatorValues);
}

bool Specimen::bearActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bearTree.isActive(currentPrice, indicatorValues);
}

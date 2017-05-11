#include "TwoTreesSpecimen.h"



TwoTreesSpecimen::TwoTreesSpecimen()
{
}

TwoTreesSpecimen::TwoTreesSpecimen(IndicatorHolder * indicators, MutationChances * mutationChances, int treeHeight) 
	: bullTree(indicators, mutationChances, treeHeight), bearTree(indicators, mutationChances, treeHeight)
{
	bullTree.generateRandom();
	bearTree.generateRandom();
}

TwoTreesSpecimen::TwoTreesSpecimen(const TwoTreesSpecimen & other) 
	: bullTree(other.bullTree), bearTree(other.bearTree)
{
}


TwoTreesSpecimen::~TwoTreesSpecimen()
{
}

bool TwoTreesSpecimen::checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bullTree.isActive(currentPrice, indicatorValues) && !bearTree.isActive(currentPrice, indicatorValues);
}

bool TwoTreesSpecimen::checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return !bullTree.isActive(currentPrice, indicatorValues) && bearTree.isActive(currentPrice, indicatorValues);
}

bool TwoTreesSpecimen::bullActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bullTree.isActive(currentPrice, indicatorValues);
}

bool TwoTreesSpecimen::bearActive(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return bearTree.isActive(currentPrice, indicatorValues);
}

shared_ptr<Specimen> TwoTreesSpecimen::cross(shared_ptr<Specimen> other)
{
	// TODO
	return make_shared<TwoTreesSpecimen>();
}

void TwoTreesSpecimen::mutate()
{
	bullTree.mutate();
	bearTree.mutate();
}

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

unique_ptr<Specimen> TwoTreesSpecimen::clone()
{
	return make_unique<TwoTreesSpecimen>(*this);
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

pair<shared_ptr<Specimen>, shared_ptr<Specimen>> TwoTreesSpecimen::cross2(shared_ptr<Specimen> other)
{
	return pair<shared_ptr<Specimen>, shared_ptr<Specimen>>();
}

void TwoTreesSpecimen::mutate()
{
	bullTree.mutate();
	bearTree.mutate();
}

string TwoTreesSpecimen::toLatex()
{
	return string();
}

int TwoTreesSpecimen::getSize()
{
	return 0;
}


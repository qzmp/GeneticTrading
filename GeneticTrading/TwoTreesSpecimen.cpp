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

bool TwoTreesSpecimen::checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues) const
{
	return bullTree.isActive(currentPrice, indicatorValues) && !bearTree.isActive(currentPrice, indicatorValues);
}

bool TwoTreesSpecimen::checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues) const
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


unique_ptr<Specimen> TwoTreesSpecimen::cross(const Specimen * other)
{
	return unique_ptr<Specimen>();
}

pair<unique_ptr<Specimen>, unique_ptr<Specimen>> TwoTreesSpecimen::cross2(const Specimen * other)
{
	return pair<unique_ptr<Specimen>, unique_ptr<Specimen>>();
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

int TwoTreesSpecimen::getHeight()
{
	return 0;
}


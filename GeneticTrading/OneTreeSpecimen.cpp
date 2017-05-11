#include "OneTreeSpecimen.h"



OneTreeSpecimen::OneTreeSpecimen()
{
}

OneTreeSpecimen::OneTreeSpecimen(IndicatorHolder * indicators, MutationChances * mutationChances, int treeHeight) 
	: strategyTree(indicators, mutationChances, treeHeight)
{
	strategyTree.generateRandom();
}

OneTreeSpecimen::OneTreeSpecimen(const OneTreeSpecimen & other) : strategyTree(other.strategyTree)
{
}


OneTreeSpecimen::~OneTreeSpecimen()
{
}

bool OneTreeSpecimen::checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return strategyTree.isActive(currentPrice, indicatorValues);
}

bool OneTreeSpecimen::checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues)
{
	return !strategyTree.isActive(currentPrice, indicatorValues);
}

shared_ptr<Specimen> OneTreeSpecimen::cross(shared_ptr<Specimen> other)
{
	return shared_ptr<Specimen>();
}

void OneTreeSpecimen::mutate()
{
	strategyTree.mutate();
}

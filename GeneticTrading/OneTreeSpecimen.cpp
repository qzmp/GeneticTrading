#include "OneTreeSpecimen.h"



OneTreeSpecimen::OneTreeSpecimen()
{
}

OneTreeSpecimen::OneTreeSpecimen(IndicatorHolder * indicators, MutationChances * mutationChances, int treeHeight) 
	: strategyTree(indicators, mutationChances, treeHeight)
{
	strategyTree.generateRandom();
}

OneTreeSpecimen::OneTreeSpecimen(const Tree* tree) : strategyTree(*tree)
{
}

OneTreeSpecimen::OneTreeSpecimen(const OneTreeSpecimen & other) : strategyTree(other.strategyTree)
{
}


OneTreeSpecimen::~OneTreeSpecimen()
{
	//cout << "Specimen destroyed";
}

unique_ptr<Specimen> OneTreeSpecimen::clone()
{
	return make_unique<OneTreeSpecimen>(*this);
}

bool OneTreeSpecimen::checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues) const
{
	return strategyTree.isActive(currentPrice, indicatorValues);
}

bool OneTreeSpecimen::checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double>& indicatorValues) const
{
	return !strategyTree.isActive(currentPrice, indicatorValues);
}

pair<unique_ptr<Specimen>, unique_ptr<Specimen>> OneTreeSpecimen::cross2(const Specimen* other)
{
	auto children = this->strategyTree.cross(static_cast<const OneTreeSpecimen*>(other)->strategyTree);
	return pair<unique_ptr<Specimen>, unique_ptr<Specimen>>(make_unique<OneTreeSpecimen>(children.first.get()), make_unique<OneTreeSpecimen>(children.second.get()));
}

void OneTreeSpecimen::mutate()
{
	strategyTree.mutate();
}

string OneTreeSpecimen::toLatex()
{
	return strategyTree.drawLatex();
}

int OneTreeSpecimen::getSize()
{
	return strategyTree.getSize();
}

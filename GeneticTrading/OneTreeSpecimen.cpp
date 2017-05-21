#include "OneTreeSpecimen.h"



OneTreeSpecimen::OneTreeSpecimen()
{
}

OneTreeSpecimen::OneTreeSpecimen(IndicatorHolder * indicators, MutationChances * mutationChances, int treeHeight) 
	: strategyTree(indicators, mutationChances, treeHeight)
{
	strategyTree.generateRandom();
}

OneTreeSpecimen::OneTreeSpecimen(unique_ptr<Tree> tree) : strategyTree(*tree)
{
}

OneTreeSpecimen::OneTreeSpecimen(const OneTreeSpecimen & other) : strategyTree(other.strategyTree)
{
}


OneTreeSpecimen::~OneTreeSpecimen()
{
}

unique_ptr<Specimen> OneTreeSpecimen::clone()
{
	return make_unique<OneTreeSpecimen>(*this);
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
	if (rand() % 2 == 0)
	{
		return make_shared<OneTreeSpecimen>(strategyTree.crossLeft(static_pointer_cast<OneTreeSpecimen>(other)->strategyTree));
	}
	else
	{
		return make_shared<OneTreeSpecimen>(strategyTree.crossRight(static_pointer_cast<OneTreeSpecimen>(other)->strategyTree));
	}
}

pair<shared_ptr<Specimen>, shared_ptr<Specimen>> OneTreeSpecimen::cross2(shared_ptr<Specimen> other)
{
	auto children = this->strategyTree.cross(static_pointer_cast<OneTreeSpecimen>(other)->strategyTree);
	return pair<shared_ptr<Specimen>, shared_ptr<Specimen>>(make_shared<OneTreeSpecimen>(move(children.first)), make_shared<OneTreeSpecimen>(move(children.second)));
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

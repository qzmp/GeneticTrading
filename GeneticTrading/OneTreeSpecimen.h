#pragma once
#include "Specimen.h"
class OneTreeSpecimen 
	: public Specimen
{
private:
	Tree strategyTree;

public:
	OneTreeSpecimen();
	OneTreeSpecimen(IndicatorHolder * indicators, MutationChances * mutationChances, int treeHeight);
	OneTreeSpecimen(const OneTreeSpecimen &other);
	~OneTreeSpecimen();

	bool checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	shared_ptr<Specimen> cross(shared_ptr<Specimen> other);
	void mutate();
};


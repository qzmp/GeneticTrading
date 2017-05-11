#pragma once

#include "Specimen.h"

class TwoTreesSpecimen
	: public Specimen
{
private:
	Tree bullTree;
	Tree bearTree;

	bool bullActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool bearActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

public:
	TwoTreesSpecimen();
	TwoTreesSpecimen(IndicatorHolder * indicators, MutationChances * mutationChances, int treeHeight);
	TwoTreesSpecimen(const TwoTreesSpecimen &other);
	~TwoTreesSpecimen();

	bool checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	shared_ptr<Specimen> cross(shared_ptr<Specimen> other);
	void mutate();
};


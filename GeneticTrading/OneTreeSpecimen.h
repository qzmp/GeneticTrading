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
	OneTreeSpecimen(const Tree* tree);
	OneTreeSpecimen(const OneTreeSpecimen & other);
	~OneTreeSpecimen();

	unique_ptr<Specimen> clone();

	bool checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) const;
	bool checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) const;

	unique_ptr<Specimen> cross(const Specimen* other);
	pair<unique_ptr<Specimen>, unique_ptr<Specimen>> cross2(const Specimen* other);
	void mutate();

	string toLatex();

	int getSize();
};


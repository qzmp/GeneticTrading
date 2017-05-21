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
	OneTreeSpecimen(unique_ptr<Tree> tree);
	OneTreeSpecimen(const OneTreeSpecimen &other);
	~OneTreeSpecimen();

	unique_ptr<Specimen> clone();

	bool checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	shared_ptr<Specimen> cross(shared_ptr<Specimen> other);
	pair<shared_ptr<Specimen>, shared_ptr<Specimen>> cross2(shared_ptr<Specimen> other);
	void mutate();

	string toLatex();

	int getSize();
};


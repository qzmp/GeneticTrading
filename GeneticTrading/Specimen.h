#pragma once

#include "Tree.h"
#include <iostream>
class Specimen
{
public:
	Specimen();
	
	Specimen(const Specimen &other);
	virtual ~Specimen();

	virtual unique_ptr<Specimen> clone() = 0;

	virtual bool checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) const = 0;
	virtual bool checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) const = 0;

	bool bullActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool bearActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	//virtual unique_ptr<Specimen> cross(const Specimen* other) = 0;
	virtual pair<unique_ptr<Specimen>, unique_ptr<Specimen>> cross2(const Specimen* other) = 0;
	virtual void mutate() = 0;

	virtual string toLatex() = 0;

	virtual int getSize() = 0;
};


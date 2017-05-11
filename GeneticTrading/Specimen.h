#pragma once

#include "Tree.h"
#include <iostream>
class Specimen
{
public:
	Specimen();
	
	Specimen(const Specimen &other);
	~Specimen();

	virtual bool checkBuySignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) = 0;
	virtual bool checkSellSignal(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues) = 0;

	bool bullActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);
	bool bearActive(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues);

	virtual shared_ptr<Specimen> cross(shared_ptr<Specimen> other) = 0;
	virtual void mutate() = 0;
};


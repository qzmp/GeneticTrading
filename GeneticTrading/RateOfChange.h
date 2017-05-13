#pragma once

#include "Indicator.h"

class RateOfChange : public Indicator
{
public:
	RateOfChange(int period);
	~RateOfChange();

	double normalizeValue(uint8_t value);

	double calculate(list<double>& pastPrices);

};


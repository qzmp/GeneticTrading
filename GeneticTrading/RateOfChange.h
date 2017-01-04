#pragma once

#include "Indicator.h"

class RateOfChange : public Indicator
{
public:
	RateOfChange(int period);
	~RateOfChange();

	bool isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue);

	double calculate(list<double>& pastPrices);
};


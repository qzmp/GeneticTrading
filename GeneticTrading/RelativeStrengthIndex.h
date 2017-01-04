#pragma once
#include "Indicator.h"
class RelativeStrengthIndex :
	public Indicator
{
public:
	RelativeStrengthIndex(int period);
	~RelativeStrengthIndex();

	bool isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue);

	double calculate(list<double>& pastPrices);
};


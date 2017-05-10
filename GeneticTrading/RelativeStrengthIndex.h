#pragma once
#include "Indicator.h"
class RelativeStrengthIndex :
	public Indicator
{
public:
	RelativeStrengthIndex(int period);
	~RelativeStrengthIndex();

	double normalizeValue(uint8_t value);

	double calculate(list<double>& pastPrices);
};


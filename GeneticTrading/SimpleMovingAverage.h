#pragma once

#include "Indicator.h"

class SimpleMovingAverage : public Indicator
{
public:
	SimpleMovingAverage(int period);
	~SimpleMovingAverage();

	double normalizeValue(uint8_t value);

	double calculate(list<double>& pastPrices);
};


#pragma once

#include "Indicator.h"

class SimpleMovingAverage : public Indicator
{
private:
	double normalizeValue(_int8 value);
public:
	SimpleMovingAverage(int period);
	~SimpleMovingAverage();

	bool isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue);

	double calculate(list<double>& pastPrices);
};


#pragma once

#include "Indicator.h"
#include "SimpleMovingAverage.h"
#include <vector>
#include <algorithm>
#include <functional>

class MovingAverageResistance 
	: public Indicator
{
private:
	int movingAveragePeriod;
	int range;
	bool isMaximum;
public:
	MovingAverageResistance(int period, int movingAveragePeriod, int range, bool maximum);
	~MovingAverageResistance();

	int getNeededDataCount();

	double normalizeValue(uint8_t value);

	double calculate(list<double>& pastPrices);
};


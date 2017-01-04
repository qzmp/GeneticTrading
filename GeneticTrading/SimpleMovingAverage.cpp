#include "SimpleMovingAverage.h"


double SimpleMovingAverage::normalizeValue(_int8 value)
{
	return 0.0;
}

SimpleMovingAverage::SimpleMovingAverage(int period) : Indicator(period, "SMA", -50, 50)
{
}

SimpleMovingAverage::~SimpleMovingAverage()
{
}

bool SimpleMovingAverage::isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue)
{
	bool result = greater ? currentPrice - normalizeValue(value) > currentIndicatorValue : currentPrice + normalizeValue(value) < currentIndicatorValue;
	
	return result;
}

double SimpleMovingAverage::calculate(list<double>& pastPrices)
{
	double sum = 0;

	for (double price : pastPrices)
	{
		sum += price;
	}
	return sum / pastPrices.size();
}
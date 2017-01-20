#include "SimpleMovingAverage.h"


SimpleMovingAverage::SimpleMovingAverage(int period) : Indicator(period, "SMA", -0.2, 0.2)
{
}

SimpleMovingAverage::~SimpleMovingAverage()
{
}

bool SimpleMovingAverage::isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue)
{
	bool result = greater ? currentPrice + (currentPrice * normalizeValue(value)) > currentIndicatorValue : currentPrice + (currentPrice * normalizeValue(value)) < currentIndicatorValue;
	
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
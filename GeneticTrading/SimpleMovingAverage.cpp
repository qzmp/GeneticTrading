#include "SimpleMovingAverage.h"


SimpleMovingAverage::SimpleMovingAverage(int period) : Indicator(period, "SMA", true)
{
}

SimpleMovingAverage::~SimpleMovingAverage()
{
}

double SimpleMovingAverage::normalizeValue(uint8_t value)
{
	return 0.0;
}

double SimpleMovingAverage::calculate(list<double>& pastPrices)
{
	double sum = 0;

	list<double>::reverse_iterator rit;

	rit = pastPrices.rbegin;
	int i = 0;
	while (i < period && rit != pastPrices.rend)
	{
		sum += *rit;
		rit++;
		i++;
	}
	return sum / period;
}
#include "RateOfChange.h"



RateOfChange::RateOfChange(int period) : Indicator(period, "ROC", false)
{
}

RateOfChange::~RateOfChange()
{
}

double RateOfChange::normalizeValue(uint8_t value)
{
	return (value / numeric_limits<uint8_t>::max() * 60) - 30;
}

double RateOfChange::calculate(list<double>& pastPrices)
{
	double lastPrice = pastPrices.back();
	double priceNPeriodsAgo;
	
	list<double>::reverse_iterator it = pastPrices.rbegin();
	advance(it, getPeriod());
	priceNPeriodsAgo = *it;

	double ROC = (lastPrice - priceNPeriodsAgo) / priceNPeriodsAgo * 100;
	return ROC;
}


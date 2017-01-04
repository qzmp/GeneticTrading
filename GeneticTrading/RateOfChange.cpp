#include "RateOfChange.h"



RateOfChange::RateOfChange(int period) : Indicator(period, "ROC", 0, 100)
{
}

RateOfChange::~RateOfChange()
{
}

bool RateOfChange::isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue)
{
	return false;
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

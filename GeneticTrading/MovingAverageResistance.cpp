#include "MovingAverageResistance.h"



MovingAverageResistance::MovingAverageResistance(int period, int movingAveragePeriod, int range, bool maximum) : Indicator(period, "MAX", true)
{
	if (!maximum)
	{
		this->name = "MAN";
	}
	this->movingAveragePeriod = movingAveragePeriod;
	this->range = range;
	this->isMaximum = maximum;
}

MovingAverageResistance::~MovingAverageResistance()
{
}

int MovingAverageResistance::getNeededDataCount()
{
	return this->range + this->movingAveragePeriod;
}

double MovingAverageResistance::normalizeValue(uint8_t value)
{
	return 0.0;
}

double MovingAverageResistance::calculate(list<double>& pastPrices)
{
	SimpleMovingAverage sma(movingAveragePeriod);
	list<double>::reverse_iterator it;
	vector<double> maValues(range);
	for (int i = 0; i < range; i++)
	{
		it = pastPrices.rbegin();
		advance(it, i);
		maValues[i] = sma.calculate(list<double>(it, pastPrices.rend()));
	}
	if (isMaximum)
		sort(maValues.begin(), maValues.end());
	else
		sort(maValues.begin(), maValues.end(), greater<double>());
	return maValues[period];
}

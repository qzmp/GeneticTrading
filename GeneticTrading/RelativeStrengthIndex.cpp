#include "RelativeStrengthIndex.h"



RelativeStrengthIndex::RelativeStrengthIndex(int period) : Indicator(period, "RSI", false)
{
}

RelativeStrengthIndex::~RelativeStrengthIndex()
{
}

double RelativeStrengthIndex::normalizeValue(uint8_t value)
{
	return (value / numeric_limits<uint8_t>::max() * 100);
}

double RelativeStrengthIndex::calculate(list<double>& pastPrices)
{
	double avgLoss = 0;
	double avgGain = 0;

	double currentChange;
	double prevPrice;

	list<double>::reverse_iterator it = pastPrices.rbegin();
	list<double>::reverse_iterator it2 = pastPrices.rbegin();
	it++;

	int i = 0;
	while (it2 != pastPrices.rend() && it != pastPrices.rend() && i < getPeriod())
	{
		currentChange = *it - *it2;
		if (currentChange < 0)
		{
			avgLoss = (avgLoss * (getPeriod() - 1) - currentChange) / getPeriod();
		}
		else if (currentChange > 0)
		{
			avgGain = (avgGain * (getPeriod() - 1) + currentChange) / getPeriod();
		}

		it++;
		it2++;
		i++;
	}
	double RS = avgGain / avgLoss;
	return 100 - 100 / (1 + RS);
}

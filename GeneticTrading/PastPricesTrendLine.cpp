#include "PastPricesTrendLine.h"



vector<pair<int,double>> PastPricesTrendLine::findLocalOptima(list<double>& pastPrices, bool max)
{
	vector<pair<int,double>> result;

	bool previousAscending = false;
	bool ascending = false;
	double lastPrice;

	list<double>::reverse_iterator rit;
	rit = pastPrices.rbegin();
	int position = 0;
	while (result.size() < 2 && rit != pastPrices.rend())
	{
		previousAscending = ascending;
		if(rit != pastPrices.rbegin())
			ascending = *rit - lastPrice > 0;
		if (position > 2)
		{
			if (max)
			{
				if (!ascending && previousAscending)
				{
					result.emplace_back(position, *rit);
				}
			}
			else
				if (ascending && !previousAscending)
				{
					result.emplace_back(position, *rit);
				}
		}
		lastPrice = *rit;
		rit++;
		position++;;
	}
	return result;
}

PastPricesTrendLine::PastPricesTrendLine(bool maximum) : Indicator(0, "UTL", true)
{
	if (!maximum)
		name = "LTL";
}

PastPricesTrendLine::~PastPricesTrendLine()
{
}

int PastPricesTrendLine::getNeededDataCount()
{
	return 30; // no nie wiem
}

double PastPricesTrendLine::normalizeValue(uint8_t value)
{
	return 0.0;
}

double PastPricesTrendLine::calculate(list<double>& pastPrices)
{
	double a, b;
	vector<pair<int, double>> optima = findLocalOptima(pastPrices, isMaximum);
	if (optima[0].second - optima[1].second == 0)
	{
		return optima[0].second;
	}
	else
	{
		a = (optima[0].second - optima[1].second) / (optima[0].first - optima[1].first);
		b = optima[0].second - (optima[0].first * a);
		return b;
	}
}

string PastPricesTrendLine::toString()
{
	return this->name;
}

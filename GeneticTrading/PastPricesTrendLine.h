#pragma once
#include "Indicator.h"
#include <vector>
class PastPricesTrendLine :
	public Indicator
{
private:
	vector<pair<int, double>> findLocalOptima(list<double>& pastPrices, bool max);
	bool isMaximum;
public:
	PastPricesTrendLine(bool maximum);
	~PastPricesTrendLine();

	int getNeededDataCount();

	double normalizeValue(uint8_t value);

	double calculate(list<double>& pastPrices);
	
	string toString();
};


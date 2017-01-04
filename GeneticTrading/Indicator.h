#pragma once

#include <fstream>
#include <sstream>
#include <list>
#include <limits>

using namespace std;

class Indicator
{
private:
	string name;
	int period;

	double maxValue;
	double minValue;

protected:
	virtual double normalizeValue(uint8_t value);

public:
	Indicator(int period, string name, double min, double max);
	~Indicator();

	string getName();
	int getPeriod();
	bool hasEnoughData(int dataCount);
	int getNeededDataCount();

	virtual bool isActive(bool greater, uint8_t value, double currentPrice, double currentIndicatorValue) = 0;

	virtual double calculate(list<double>& pastPrices) = 0;
};


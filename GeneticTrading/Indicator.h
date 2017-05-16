#pragma once

#include <fstream>
#include <sstream>
#include <list>
#include <limits>

using namespace std;

class Indicator
{
protected:
	string name;
	int period;

	bool trendIndicator;

public:
	Indicator(int period, string name, bool isTrendIndicator);
	virtual ~Indicator();

	string getName();
	int getPeriod();
	bool hasEnoughData(int dataCount);
	virtual int getNeededDataCount();

	bool isTrendIndicator();
	virtual double normalizeValue(uint8_t value) = 0;

	virtual double calculate(list<double>& pastPrices) = 0;

	virtual string toString();
};


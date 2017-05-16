#include "Indicator.h"

Indicator::Indicator(int period, string name, bool isTrendIndicator)
{
	this->period = period;
	this->name = name;
	this->trendIndicator = isTrendIndicator;
}

Indicator::~Indicator()
{
}

string Indicator::getName()
{
	return this->name;
}

int Indicator::getPeriod()
{
	return this->period;
}

bool Indicator::hasEnoughData(int dataCount)
{
	return getNeededDataCount() <= dataCount;
}

int Indicator::getNeededDataCount()
{
	return period;
}

bool Indicator::isTrendIndicator()
{
	return trendIndicator;
}

string Indicator::toString()
{
	return this->name + "(" + to_string(this->period) + ")";
}

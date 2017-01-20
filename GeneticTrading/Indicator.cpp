#include "Indicator.h"

double Indicator::normalizeValue(uint8_t value)
{
	return (double)value / numeric_limits<uint8_t>::max() * (abs(minValue) + abs(maxValue)) - abs(minValue);
}

Indicator::Indicator(int period, string name, double min, double max)
{
	this->period = period;
	this->name = name;
	this->minValue = min;
	this->maxValue = max;
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
	return this->period <= dataCount;
}

int Indicator::getNeededDataCount()
{
	return period;
}

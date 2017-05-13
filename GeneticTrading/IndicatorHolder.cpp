#include "IndicatorHolder.h"



IndicatorHolder::IndicatorHolder()
{
}


IndicatorHolder::~IndicatorHolder()
{
}

void IndicatorHolder::addIndicator(shared_ptr<Indicator> indicator)
{
	if (indicator->isTrendIndicator())
		trendIndicators.push_back(indicator);
	else
		oscillators.push_back(indicator);

	allIndicators.push_back(indicator);
}

shared_ptr<Indicator> IndicatorHolder::getRandomOscillator()
{
	int randomIndicatorIndex = rand() % oscillators.size();
	return oscillators[randomIndicatorIndex];
}

shared_ptr<Indicator> IndicatorHolder::getRandomTrendIndicator()
{
	int randomIndicatorIndex = rand() % trendIndicators.size();
	return trendIndicators[randomIndicatorIndex];
}

shared_ptr<Indicator> IndicatorHolder::getRandom()
{
	int randomIndicatorIndex = rand() % allIndicators.size();
	return allIndicators[randomIndicatorIndex];
}

bool IndicatorHolder::hasEnoughDataPoints(int count)
{
	bool hasEnoughData = true;
	for (auto& i : allIndicators)
	{
		hasEnoughData &= (i->getNeededDataCount() <= count);
	}
	return hasEnoughData;
}

vector<shared_ptr<Indicator>>* IndicatorHolder::getAllIndicators()
{
	return &allIndicators;
}

int IndicatorHolder::getTrendIndicatorCount()
{
	return trendIndicators.size();
}

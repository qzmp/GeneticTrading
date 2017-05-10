#pragma once

#include <vector>
#include <memory>
#include "Indicator.h"

using namespace std;
class IndicatorHolder
{
private:
	vector<shared_ptr<Indicator>> oscillators;
	vector<shared_ptr<Indicator>> trendIndicators;

	vector<shared_ptr<Indicator>> allIndicators;
public:
	IndicatorHolder();
	~IndicatorHolder();

	void addIndicator(shared_ptr<Indicator> indicator);
	shared_ptr<Indicator> getRandomOscillator();
	shared_ptr<Indicator> getRandomTrendIndicator();
	shared_ptr<Indicator> getRandom();

	vector<shared_ptr<Indicator>> getAllIndicators();
};


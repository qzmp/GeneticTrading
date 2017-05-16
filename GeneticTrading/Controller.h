#pragma once

#include "DataSet.h"
#include "SimpleMovingAverage.h"
#include "RateOfChange.h"
#include "RelativeStrengthIndex.h"
#include "Specimen.h"
#include "Backtester.h"
#include "GeneticController.h"
#include "MovingAverageResistance.h"
#include "PastPricesTrendLine.h"

class Controller
{
public:
	Controller();
	~Controller();

	double testMutation(double min, double max, double step);
};

int main();
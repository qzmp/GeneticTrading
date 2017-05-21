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
private:
	double countStandardDeviation(list<int>& values);
public:
	Controller();
	~Controller();

	void testMutation(GeneticController gt, double min, double max, double step);
	void testPopSize(GeneticController gt, double min, double max, double step);
	void testGenCount(GeneticController gt, double min, double max, double step);
	void testMaxTreeSize(GeneticController gt, double min, double max, double step);
	void testCrossChance(GeneticController gt, double min, double max, double step);
	void testTourneySize(GeneticController gt, double min, double max, double step);
	void testParams(GeneticController& gt);

	void runXTimes(GeneticController& gt, int count, ofstream& filestream, double testedValue);
};

int main();
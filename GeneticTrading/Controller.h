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
	vector<double> countQuartiles(list<int> & values);
	double countMedian(list<int> & values);

	

public:
	Controller();
	~Controller();

	void testMutation(GeneticController gt, double min, double max, double step, DataSet & testingSet);
	void testPopSize(GeneticController gt, double min, double max, double step, DataSet & testingSet);
	void testGenCount(GeneticController gt, double min, double max, double step, DataSet & testingSet);
	void testMaxTreeSize(GeneticController gt, double min, double max, double step, DataSet & testingSet);
	void testCrossChance(GeneticController gt, double min, double max, double step, DataSet & testingSet);
	void testTourneySize(GeneticController gt, double min, double max, double step, DataSet & testingSet);
	void testParams(GeneticController& gt, DataSet & testingSet);

	vector<DataSet> getDataSets(IndicatorHolder & indicators);
	void testDataSets(GeneticController & gt, vector<DataSet> & dataSets);
	void testDataSet(GeneticController & gt, vector<DataSet> & dataSets, ofstream & filestream);

	void runXTimes(GeneticController& gt, int count, ofstream& filestream, double testedValue, DataSet & testingSet);

	void test2(GeneticController& gt, string& filePrefix, ofstream & summaryStream);
	void runXTimes2(GeneticController & gt, int count, vector<DataSet> & testingSets, string & filePrefix, ofstream & summaryFile);

	vector<vector<DataSet>> testingSets;
	vector<DataSet> trainingSet;
};

int main();
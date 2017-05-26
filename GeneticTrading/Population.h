#pragma once

#include "OneTreeSpecimen.h"
#include "Backtester.h"
#include "MutationChances.h"
#include <numeric>
#include <algorithm>

class Population
{
private:
	vector<unique_ptr<Specimen>> specimens;
	vector<double> ratings;

	DataSet *dataSet;

	Backtester backtester;
	
	vector<int> randomizeTourneyGroup(int size);
	int tourney(vector<int>& tourneyGroup);

public:
	Population(DataSet *dataSet, int maxSize);
	//Population(const Population &other);
	~Population();

	void generateRandom(MutationChances &mt, IndicatorHolder &indicators, int treeHeight);

	unique_ptr<Specimen> select(int tourneySize);
	
	void rateAll();
	unique_ptr<Population> commenceCrossing(int tourneySize, double crossingChance);
	void mutateAllSpecimen();

	void insertNewSpecimen(unique_ptr<Specimen> specimen);

	unique_ptr<Specimen> getBestSpecimen();
	double getBestRating();
	double getAverageRating();

	DataSet* getDataSet();
	MutationChances* getMutationChances();

	double getAvgSize();
};


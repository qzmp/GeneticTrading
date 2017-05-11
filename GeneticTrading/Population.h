#pragma once

#include "OneTreeSpecimen.h"
#include "Backtester.h"
#include "MutationChances.h"
#include <numeric>
#include <algorithm>

class Population
{
private:
	vector<shared_ptr<Specimen>> specimens;
	vector<double> ratings;

	DataSet *dataSet;

	Backtester backtester;
	
	vector<int> randomizeTourneyGroup(int size);
	int tourney(vector<int>& tourneyGroup);

public:
	Population(DataSet *dataSet, int maxSize);
	Population(const Population &other);
	~Population();

	void generateRandom(MutationChances &mt, IndicatorHolder &indicators, int treeHeight);

	shared_ptr<Specimen> select(int tourneySize);
	
	void rateAll();
	Population* commenceCrossing(int tourneySize, double crossingChance);
	void mutateAllSpecimen();

	void insertNewSpecimen(shared_ptr<Specimen> specimen);

	shared_ptr<Specimen> getBestSpecimen();
	double getBestRating();
	double getAverageRating();

	DataSet* getDataSet();
	MutationChances* getMutationChances();
};


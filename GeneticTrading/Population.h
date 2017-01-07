#pragma once

#include "Specimen.h"
#include "Backtester.h"

class Population
{
private:
	vector<Specimen> specimens;
	vector<double> ratings;

	DataSet * dataSet;

	Backtester backtester;
	
	vector<int> randomizeTourneyGroup(int size);
	int tourney(vector<int>& tourneyGroup);

public:
	Population();
	~Population();

	Specimen* select();
	
	void rateAll();
};


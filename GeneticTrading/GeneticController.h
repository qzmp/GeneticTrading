#pragma once

#include "Population.h"
#include "Specimen.h"
#include "MutationChances.h"
#include "DateTime.h"
#include <chrono>
#include <list>

class GeneticController
{
private:
	unique_ptr<Population> population;

	int tourneySize;
	double crossingChance;
	MutationChances &mt;
	IndicatorHolder &indicators;
	DataSet &dataSet;
	int treeHeight;
	int popSize;
	int generationCount;

	list<vector<double>> history;
	ofstream fileStream;

	void generateNewPopulation(MutationChances &mt, IndicatorHolder &indicators, DataSet &dataSet, int treeHeight, int size);

	void createFileStream(MutationChances &mt, DataSet &ds, int popSize);
	void saveCurrentRatings();
	void writeHistory();

public:

	GeneticController(double tourneySize, double crossingChance, MutationChances &mt, IndicatorHolder &indicators, 
		DataSet &dataSet, int treeHeight, int popSize, int generationCount);
	GeneticController(const GeneticController& other);
	~GeneticController();

	shared_ptr<Specimen> startEvolution();
	void nextGeneration();

	void setTourneySize(double tourneySize);
	void setCrossingChance(double crossingChance);
	void setMutationChances(MutationChances& mt);
	void setTreeHeight(int treeHeight);
	void setPopSize(int popSize);
	void setGenCount(int genCount);

	DataSet* getDataSet();

	void reset();
};


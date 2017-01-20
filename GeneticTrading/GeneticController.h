#pragma once

#include "Population.h"
#include "Specimen.h"
#include "MutationChances.h"
#include "DateTime.h"
#include <list>

class GeneticController
{
private:
	unique_ptr<Population> population;

	double crossingChance;
	int tourneySize;
	int generationCount;

	list<vector<double>> history;
	ofstream fileStream;

	void generateNewPopulation(MutationChances &mt, vector<shared_ptr<Indicator>> &indicators, DataSet &dataSet, int treeHeight, int size);

	void createFileStream(MutationChances &mt, DataSet &ds, int popSize);
	void saveCurrentRatings();
	void writeHistory();

public:
	GeneticController();
	GeneticController(int tourneySize, double crossingChance, MutationChances &mt, vector<shared_ptr<Indicator>> &indicators, DataSet &dataSet, int treeHeight, int popSize, int generationCount);
	~GeneticController();

	Specimen startEvolution();
	void nextGeneration();
};


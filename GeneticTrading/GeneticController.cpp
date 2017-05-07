#include "GeneticController.h"



void GeneticController::generateNewPopulation(MutationChances &mt, vector<shared_ptr<Indicator>>& indicators, DataSet &dataSet, int treeHeight, int size)
{
	population = unique_ptr<Population>(new Population(&dataSet, size));
	population->generateRandom(mt, indicators, treeHeight);
}

void GeneticController::createFileStream(MutationChances &mt, DataSet &ds, int popSize)
{
	string filename = //"results/test.csv";
		"results/" + to_string(ds.getStart().getDay()) + " "
		+ to_string(ds.getStart().getMonth()) + " "
		+ to_string(ds.getStart().getYear()) + ";"
		+ to_string(ds.getEnd().getDay()) + " "
		+ to_string(ds.getEnd().getMonth()) + " "
		+ to_string(ds.getEnd().getYear()) + " "
		+ mt.toString()
		+ "," + to_string(crossingChance)
		+ "," + to_string(tourneySize)
		+ "," + to_string(popSize)
		+ "," + to_string(generationCount) + ".csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);
}

void GeneticController::saveCurrentRatings()
{
	vector<double> h = { population->getAverageRating(), population->getBestRating() };
	history.push_back(h);
}

void GeneticController::writeHistory()
{
	if (fileStream.is_open())
	{
		int i = 1;
		for (auto it = history.begin(); it != history.end(); it++)
		{
			fileStream << i << ";" << it->operator[](0) << ";" << it->operator[](1) << "\n";
			i++;
		}
	}
}

GeneticController::GeneticController()
{
}

GeneticController::GeneticController(int tourneySize, double crossingChance, MutationChances &mt, vector<shared_ptr<Indicator>> &indicators, DataSet &dataSet, int treeHeight, int popSize, int generationCount) 
	: tourneySize(tourneySize), crossingChance(crossingChance), generationCount(generationCount)
{
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

GeneticController::~GeneticController()
{
}

Backtester::TransactionData GeneticController::startEvolution()
{
	for (int i = 0; i < generationCount; i++)
	{
		nextGeneration();
	}
	
	population->rateAll();
	saveCurrentRatings();
	writeHistory();
	Backtester bt;
	return bt.backtest(*population->getDataSet(), population->getBestSpecimen());
}

void GeneticController::nextGeneration()
{
	population->rateAll();
	saveCurrentRatings();
	Population * newPopulation = population->commenceCrossing(tourneySize, crossingChance);
	population.reset(newPopulation);
	population->mutateAllSpecimen();
}

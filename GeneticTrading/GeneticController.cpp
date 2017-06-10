#include "GeneticController.h"



void GeneticController::generateNewPopulation(MutationChances &mt, IndicatorHolder& indicators, DataSet &dataSet, int treeHeight, int size)
{
	population = unique_ptr<Population>(new Population(size));
	population->generateRandom(mt, indicators, treeHeight);
	history = list<vector<double>>();
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
	vector<double> h = { population->getAverageRating(), population->getBestRating(), population->getAvgSize(), population->getAvgHeight() };
	history.push_back(h);
}

void GeneticController::writeHistory()
{
	if (fileStream.is_open())
	{
		int i = 0;
		for (auto it = history.begin(); it != history.end(); it++)
		{
			fileStream << i << ";" << it->operator[](0) << ";" << it->operator[](1);
			fileStream << ";" << it->operator[](2);
			fileStream << ";" << it->operator[](3);
			fileStream << "\n";
			i++;
		}
	}
	fileStream << endl;
}


GeneticController::GeneticController(double tourneySize, double crossingChance, MutationChances &mt, IndicatorHolder &indicators, DataSet &dataSet, int treeHeight, int popSize, int generationCount) 
	: tourneySize(tourneySize * popSize), crossingChance(crossingChance), mt(mt), indicators(indicators), dataSet(dataSet), treeHeight(treeHeight), popSize(popSize), generationCount(generationCount)
{
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

GeneticController::GeneticController(const GeneticController & other) 
	: GeneticController(other.tourneySize, other.crossingChance, other.mt, other.indicators, other.dataSet, other.treeHeight, other.popSize, other.generationCount)
{
	this->tourneySize = other.tourneySize;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

GeneticController::~GeneticController()
{
}

unique_ptr<Specimen> GeneticController::startEvolution()
{
	for (int i = 0; i < generationCount; i++)
	{
		nextGeneration();
	}
	
	population->rateAll(this->treeHeight, this->dataSet);
	saveCurrentRatings();
	writeHistory();
	Backtester bt;
	fileStream.close();
	return population->getBestSpecimen();
}

void GeneticController::nextGeneration()
{
	population->rateAll(this->treeHeight, this->dataSet);
	saveCurrentRatings();
	population.swap(population->commenceCrossing(tourneySize, crossingChance));
	population->mutateAllSpecimen();
}

void GeneticController::setTourneySize(double tourneySize)
{
	this->tourneySize = tourneySize * popSize;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

void GeneticController::setCrossingChance(double crossingChance)
{
	this->crossingChance = crossingChance;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

void GeneticController::setMutationChances(MutationChances & mt)
{
	this->mt = mt;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

void GeneticController::setTreeHeight(int treeHeight)
{
	this->treeHeight = treeHeight;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

void GeneticController::setPopSize(int popSize)
{
	this->popSize = popSize;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

void GeneticController::setGenCount(int genCount)
{
	this->generationCount = genCount;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

DataSet* GeneticController::getDataSet()
{
	return &dataSet;
}

void GeneticController::reset()
{
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

void GeneticController::setDataSet(DataSet & dataSet)
{
	this->dataSet = dataSet;
	generateNewPopulation(mt, indicators, dataSet, treeHeight, popSize);
	createFileStream(mt, dataSet, popSize);
}

#include "Population.h"


vector<int> Population::randomizeTourneyGroup(int size)
{
	vector<int> result(size);
	for (int i = 0; i < size; i++)
	{
		result[i] = rand() % specimens.size();
	}
	return result;
}

int Population::tourney(vector<int>& tourneyGroup)
{
	int maxRating = ratings[tourneyGroup[0]];
	int bestPos = tourneyGroup[0];
	for (int i = 0; i < tourneyGroup.size(); i++)
	{
		if (ratings[tourneyGroup[i]] > maxRating)
		{
			maxRating = ratings[tourneyGroup[i]];
			bestPos = tourneyGroup[i];
		}
	}
	return bestPos;
}

Population::Population(DataSet * dataSet, int maxSize) : dataSet(dataSet), ratings(maxSize)
{
	specimens.reserve(maxSize);
}

Population::Population(const Population & other)
	: specimens(other.specimens), ratings(other.ratings), dataSet(other.dataSet)
{
}

Population::~Population()
{
	cout << "population destroyed" << endl;
}

void Population::generateRandom(MutationChances & mt, IndicatorHolder& indicators, int treeHeight)
{
	for (int i = 0; i < specimens.capacity(); i++)
	{
		specimens.push_back(make_shared<OneTreeSpecimen>(&indicators, &mt, treeHeight)); // Capacity is optimized
	}
}

shared_ptr<Specimen> Population::select(int tourneySize)
{
	return specimens[tourney(randomizeTourneyGroup(tourneySize))];
}

void Population::rateAll()
{
	ratings = vector<double>(specimens.size());
	Backtester::TransactionData transactionData;
	for (int i = 0; i < specimens.size(); i++)
	{
		transactionData = backtester.backtest(*dataSet, specimens[i]);
		ratings[i] = transactionData.getTotalPipGain();
	}
}

unique_ptr<Population> Population::commenceCrossing(int tourneySize, double crossingChance)
{
	unique_ptr<Population> newPopulation = make_unique<Population>(dataSet, specimens.size());
	shared_ptr<Specimen> firstSpecimen, secondSpecimen;
	for (int i = 0; i < specimens.size(); i += 2)
	{
		firstSpecimen = select(tourneySize);
		secondSpecimen = select(tourneySize);
		if (rand() / double(RAND_MAX) < crossingChance)
		{
			
			auto newSpecimens = firstSpecimen->cross2(secondSpecimen);
			newPopulation->insertNewSpecimen(newSpecimens.first);
			newPopulation->insertNewSpecimen(newSpecimens.second);

			//newPopulation->insertNewSpecimen(firstSpecimen->cross(secondSpecimen));
		}
		else
		{
			newPopulation->insertNewSpecimen(shared_ptr<Specimen>(firstSpecimen->clone()));
			newPopulation->insertNewSpecimen(shared_ptr<Specimen>(secondSpecimen->clone()));
		}
	}
	return newPopulation;
}

void Population::mutateAllSpecimen()
{
	for (auto& spec : specimens)
	{
		spec->mutate();
	}
}

void Population::insertNewSpecimen(shared_ptr<Specimen>& specimen)
{
	specimens.push_back(specimen);
}

shared_ptr<Specimen> Population::getBestSpecimen()
{
	int bestGrade = 0;
	int bestIndex = 0;
	for (int i = 0; i < ratings.size(); i++)
	{
		if (ratings[i] > bestGrade)
		{
			bestGrade = ratings[i];
			bestIndex = i;
		}
	}
	return specimens[bestIndex];
}

double Population::getBestRating()
{
	return *max_element(ratings.begin(), ratings.end());
}

double Population::getAverageRating()
{
	return accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
}

DataSet * Population::getDataSet()
{
	return dataSet;
}

double Population::getAvgSize()
{
	int sum = 0;
	for (auto& spec : specimens)
	{
		sum += spec->getSize();
	}
	return sum / specimens.size();
}

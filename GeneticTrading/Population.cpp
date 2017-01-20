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
	//cout << "population destroyed" << endl;
}

void Population::generateRandom(MutationChances & mt, vector<shared_ptr<Indicator>>& indicators, int treeHeight)
{
	for (int i = 0; i < specimens.capacity(); i++)
	{
		specimens.emplace_back(&indicators, &mt, treeHeight); // Capacity is optimized
	}
}

Specimen * Population::select(int tourneySize)
{
	return &specimens[tourney(randomizeTourneyGroup(tourneySize))];
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

Population* Population::commenceCrossing(int tourneySize, double crossingChance)
{
	unique_ptr<Population> newPopulation = make_unique<Population>(dataSet, specimens.size());
	Specimen *firstSpecimen, *secondSpecimen;
	for (int i = 0; i < specimens.size(); i++)
	{
		firstSpecimen = select(tourneySize);

		if (rand() < crossingChance)
		{
			secondSpecimen = select(tourneySize);
			newPopulation->insertNewSpecimen(firstSpecimen->cross(*secondSpecimen));
		}
		else
		{
			newPopulation->insertNewSpecimen(*firstSpecimen);
		}
	}
	return newPopulation.release();
}

void Population::mutateAllSpecimen()
{
	for (Specimen &spec : specimens)
	{
		spec.mutate();
	}
}

void Population::insertNewSpecimen(Specimen & specimen)
{
	specimens.push_back(specimen);
}

Specimen Population::getBestSpecimen()
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

#include "Population.h"



Population::Population()
{
}


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

Population::~Population()
{
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

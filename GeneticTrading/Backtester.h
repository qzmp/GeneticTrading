#pragma once

#include "DataSet.h"
#include "Specimen.h"


class Backtester
{
public:
	class TransactionData
	{
		friend class Backtester;
	private:
		int totalPipGain;

		list<double> buyPrices;
		list<double> sellPrices;

		int goodTransactionCount;
		int badTransactionCount;

	public:
		TransactionData() : totalPipGain(0), goodTransactionCount(0), badTransactionCount() {};
		~TransactionData() {};

		int getTotalPipGain();
		int getTransactionCount();
		int getGoodTransactionCount();
		int getBadTransactionCount();
	};


private:
	DataSet dataSet;
	TransactionData transactionData;

	bool bought;
	bool sold;
	int priceToPips(double price);
	int processTick(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues, Specimen & strategy);

public:
	
	Backtester();
	~Backtester();

	TransactionData & backtest(DataSet & dataSet, Specimen & strategy);
};
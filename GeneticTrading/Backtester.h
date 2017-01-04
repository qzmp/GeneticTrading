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

	public:
		TransactionData() : totalPipGain(0) {};
		~TransactionData() {};
	};


private:
	DataSet dataSet;
	TransactionData transactionData;

	bool bought;
	bool sold;
	int priceToPips(double price);
	int processTick(double currentPrice, map<shared_ptr<Indicator>, double> indicatorValues, Specimen & strategy);

public:
	
	Backtester();
	~Backtester();

	TransactionData & backtest(DataSet & dataSet, Specimen & strategy);
};
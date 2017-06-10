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
		int gains;
		int losses;

		list<double> buyPrices;
		list<double> sellPrices;

		int goodTransactionCount;
		int badTransactionCount;

	public:
		TransactionData() : gains(0), losses(0), goodTransactionCount(0), badTransactionCount(0) {};
		~TransactionData() {};

		int getPipGainWithProvision(int provision);
		int getTotalPipGain();	
		int getGains();
		int getLosses();
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
	int processTick(double currentPrice, map<shared_ptr<Indicator>, double> & indicatorValues, const Specimen* strategy);
	int provision;

public:
	
	Backtester();
	~Backtester();

	TransactionData & backtest(DataSet & dataSet, const Specimen* strategy);
	TransactionData & backtestTickData(DataSet & dataSet, const Specimen* strategy);
};
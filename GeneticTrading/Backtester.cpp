#include "Backtester.h"



int Backtester::priceToPips(double price)
{
	return price * 100000;
}

int Backtester::processTick(double currentPrice, map<shared_ptr<Indicator>, double> indicatorValues, Specimen & strategy)
{
	if (!bought && !sold) {
		if (strategy.bearActive(currentPrice, indicatorValues))
		{
			bought = true;
			transactionData.buyPrices.push_back(currentPrice);
		}
		else if (strategy.bearActive(currentPrice, indicatorValues))
		{
			sold = true;
			transactionData.sellPrices.push_back(currentPrice);
		}
	}
	else if(bought)
	{
		if (strategy.bearActive(currentPrice, indicatorValues))
		{
			double gain = currentPrice - transactionData.buyPrices.back();
			transactionData.totalPipGain += priceToPips(gain);
			transactionData.sellPrices.push_back(currentPrice);

			bought = false;
			sold = true;
		}
	}
	else if (sold)
	{
		if (strategy.bullActive(currentPrice, indicatorValues))
		{
			double gain = transactionData.sellPrices.back() - currentPrice;
			transactionData.totalPipGain += priceToPips(gain);
			transactionData.buyPrices.push_back(currentPrice);

			bought = true;
			sold = false;
		}
	}
	return 0;
}

Backtester::Backtester()
{
}


Backtester::~Backtester()
{
}

Backtester::TransactionData & Backtester::backtest(DataSet & dataSet, Specimen & strategy)
{
	bought = false;
	sold = false; 
	transactionData = TransactionData();

	map<shared_ptr<Indicator>, double> indicatorValues;
	int i = 0;
	while (i < dataSet.getSize())
	{
		indicatorValues = dataSet.getIndicatorValues(i);
		processTick(dataSet.getOpenPrice(i), indicatorValues, strategy);
		processTick(dataSet.getHighPrice(i), indicatorValues, strategy);
		processTick(dataSet.getLowPrice(i), indicatorValues, strategy);
		processTick(dataSet.getClosePrice(i), indicatorValues, strategy);
		i++;
	}
	if (bought)
	{
		double gain = dataSet.getClosePrice(i - 1) - transactionData.buyPrices.back();
		transactionData.totalPipGain += priceToPips(gain);
		
		bought = false;
		sold = false;
		
	}
	else if (sold)
	{
		double gain = transactionData.sellPrices.back() - dataSet.getClosePrice(i - 1);
		transactionData.totalPipGain += priceToPips(gain);
		
		bought = false;
		sold = false;
	}
	return transactionData;
}

int Backtester::TransactionData::getTotalPipGain()
{
	return this->totalPipGain;
}

#include "Backtester.h"



int Backtester::priceToPips(double price)
{
	return price * 100000;
}

int Backtester::processTick(double currentPrice, map<shared_ptr<Indicator>, double> &indicatorValues, const Specimen* strategy)
{
	if (!bought && !sold) {
		if (strategy->checkBuySignal(currentPrice, indicatorValues))
		{
			bought = true;
			transactionData.buyPrices.push_back(currentPrice);
		}
		else if (strategy->checkSellSignal(currentPrice, indicatorValues))
		{
			sold = true;
			transactionData.sellPrices.push_back(currentPrice);
		}
	}
	else if(bought)
	{
		if (strategy->checkSellSignal(currentPrice, indicatorValues))
		{
			double gain = transactionData.buyPrices.back() - currentPrice;
			if (gain > 0)
			{
				transactionData.gains += priceToPips(gain);
				transactionData.goodTransactionCount++;
			}
			else
			{
				transactionData.losses += -priceToPips(gain);
				transactionData.badTransactionCount++;
			}

			transactionData.sellPrices.push_back(currentPrice);

			bought = false;
			sold = true;
		}
	}
	else if (sold)
	{
		if (strategy->checkBuySignal(currentPrice, indicatorValues))
		{
			double gain =  currentPrice - transactionData.sellPrices.back();
			if (gain > 0)
			{
				transactionData.gains += priceToPips(gain);
				transactionData.goodTransactionCount++;
			}
			else
			{
				transactionData.losses += -priceToPips(gain);
				transactionData.badTransactionCount++;
			}
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

Backtester::TransactionData & Backtester::backtest(DataSet & dataSet, const Specimen* strategy)
{
	bought = false;
	sold = false; 
	transactionData = TransactionData();

	map<shared_ptr<Indicator>, double>* indicatorValues;
	int i = 0;
	while (i < dataSet.getSize())
	{
		indicatorValues = dataSet.getIndicatorValues(i);
		processTick(dataSet.getOpenPrice(i), *indicatorValues, strategy);
		if (rand() % 2 == 0) {
			processTick(dataSet.getHighPrice(i), *indicatorValues, strategy);
			processTick(dataSet.getLowPrice(i), *indicatorValues, strategy);
		}
		else
		{
			processTick(dataSet.getLowPrice(i), *indicatorValues, strategy);
			processTick(dataSet.getHighPrice(i), *indicatorValues, strategy);
		}
		
		processTick(dataSet.getClosePrice(i), *indicatorValues, strategy);
		i++;
	}
	if (bought)
	{
		double gain = dataSet.getClosePrice(i - 1) - transactionData.buyPrices.back();
		if (gain > 0)
		{
			transactionData.gains += priceToPips(gain);
			transactionData.goodTransactionCount++;
		}
		else
		{
			transactionData.losses += -priceToPips(gain);
			transactionData.badTransactionCount++;
		}
		
		bought = false;
		sold = false;
		
	}
	else if (sold)
	{
		double gain = transactionData.sellPrices.back() - dataSet.getClosePrice(i - 1);
		if (gain > 0)
		{
			transactionData.gains += priceToPips(gain);
			transactionData.goodTransactionCount++;
		}
		else
		{
			transactionData.losses += -priceToPips(gain);
			transactionData.badTransactionCount++;
		}
		
		bought = false;
		sold = false;
	}
	return transactionData;
}


int Backtester::TransactionData::getPipGainWithProvision(int provision)
{
	return this->gains - this->losses - getTransactionCount() * provision;
}

int Backtester::TransactionData::getTotalPipGain()
{
	return this->gains - this->losses;
}

int Backtester::TransactionData::getGains()
{
	return this->gains;
}

int Backtester::TransactionData::getLosses()
{
	return this->losses;
}

int Backtester::TransactionData::getTransactionCount()
{
	return goodTransactionCount + badTransactionCount;
}

int Backtester::TransactionData::getGoodTransactionCount()
{
	return goodTransactionCount;
}

int Backtester::TransactionData::getBadTransactionCount()
{
	return badTransactionCount;
}

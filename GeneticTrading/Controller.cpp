#include "Controller.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

int main()
{
	DataSet data;
	vector<shared_ptr<Indicator>> indicators;
	/*
	for (int i = 5; i < 200; i += 10)
	{
		indicators.push_back(shared_ptr<Indicator>(new SimpleMovingAverage(i)));
	}
	*/
	//indicators.push_back(shared_ptr<Indicator>(new RateOfChange(3)));
	//indicators.push_back(shared_ptr<Indicator>(new RateOfChange(12)));
	indicators.push_back(shared_ptr<Indicator>(new RelativeStrengthIndex(14)));
	data.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.01.2016 00:00:00"), DateTime("15.01.2016 00:00:00"), indicators);
	Specimen spec(indicators, 2);
	Backtester bt;
	Backtester::TransactionData td = bt.backtest(data, spec);
	
	return 0;
}

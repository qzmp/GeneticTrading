#include "Controller.h"



Controller::Controller()
{
}


Controller::~Controller()
{
}

double Controller::testMutation(double min, double max, double step)
{
	DataSet data;
	IndicatorHolder indicators;

	for (int i = 10; i < 200; i += 20)
	{
		indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(i)));
	}

	indicators.addIndicator(shared_ptr<Indicator>(new RateOfChange(3)));
	indicators.addIndicator(shared_ptr<Indicator>(new RateOfChange(12)));
	indicators.addIndicator(shared_ptr<Indicator>(new RelativeStrengthIndex(14)));
	data.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.01.2016 00:00:00"), DateTime("15.01.2016 00:00:00"), indicators);
	
	ofstream fileStream;
	string filename = "results/mutationTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);
	
	double x = 0.1;

	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		MutationChances *mc = new MutationChances(x,x,x,x,x,x,x);
		
		pipSum = 0;
		transactionSum = 0;
		for (int j = 0; j < 10; j++)
		{
			GeneticController gt(10, 0.2, *mc, indicators, data, 3, 200, i);
			//Backtester::TransactionData td = gt.startEvolution();

			//pipSum += td.getTotalPipGain();
			//transactionSum += td.getTransactionCount();
			
		}
		fileStream << i << ";" << pipSum / 10<< ";" << transactionSum / 10 << endl;
		delete mc;
	}
	return 0;
}

int main()
{
	srand(time(0));
	Controller c;
	//c.testMutation(90, 200, 20);

	DataSet data;

	IndicatorHolder indicators;
	for (int i = 10; i < 200; i += 20)
	{
		//indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(i)));
	}
	indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(2)));
	indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(3)));
	indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(6)));
	indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(12)));
	indicators.addIndicator(shared_ptr<Indicator>(new SimpleMovingAverage(26)));


	//indicators.addIndicator(shared_ptr<Indicator>(new RateOfChange(3)));
	//indicators.addIndicator(shared_ptr<Indicator>(new RateOfChange(12)));
	//indicators.addIndicator(shared_ptr<Indicator>(new RelativeStrengthIndex(14)));

	data.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.01.2016 00:00:00"), DateTime("15.01.2016 00:00:00"), indicators);
	MutationChances *mc = new MutationChances(0.01, 0.01, 0.01, 0.01, 0.01 ,0.01, 0.01);
	//MutationChances *mc = new MutationChances(0, 0, 0, 0, 1, 1, 1);

	/*
	Specimen spec(&indicators, mc, 2);
	Backtester bt;
	Backtester::TransactionData td = bt.backtest(data, spec);
	*/
	//DataSet data2;
	//data2.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("15.01.2016 00:00:00"), DateTime("22.01.2016 00:00:00"), indicators);

	GeneticController gt(40, 0.1, *mc, indicators, data, 5, 200, 200);
	/*int bestscore = 0;
	for (int i = 0; i < 100; i++)
	{
		backtester::transactiondata td = gt.startevolution();
		backtester bt;
		backtester::transactiondata td = bt.backtest(data2, best);
		if (td.gettotalpipgain() > bestscore)
		{
			bestscore = td.gettotalpipgain();
		}
	}*/

	//Specimen best = gt.startEvolution();

	//Backtester bt;
	shared_ptr<Specimen> best = gt.startEvolution();
	cout << best->toLatex();

	return 0;
}

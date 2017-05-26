#include "Controller.h"



double Controller::countStandardDeviation(list<int>& values)
{
	double gainsSum = accumulate(begin(values), end(values), 0.0);
	double gainsMean = gainsSum / values.size();

	vector<double> diff(values.size());
	transform(values.begin(), values.end(), diff.begin(), [gainsMean](double x) { return x - gainsMean; });
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = sqrt(sq_sum / values.size());
	return stdev;
}

Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::testMutation(GeneticController gt, double min, double max, double step)
{
	ofstream fileStream;
	string filename = "results/mutationTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);
	
	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		MutationChances mc(0.05, 0.02, 0.05, i);
		gt.setMutationChances(mc);

		runXTimes(gt, 10, fileStream, i);
	}
}

void Controller::testPopSize(GeneticController gt, double min, double max, double step)
{
	ofstream fileStream;
	string filename = "results/popSizeTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		int popSize = i;
		gt.setPopSize(popSize);

		runXTimes(gt, 10, fileStream, i);
	}
}

void Controller::testGenCount(GeneticController gt, double min, double max, double step)
{
	ofstream fileStream;
	string filename = "results/genCountTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		int genCount = i;
		gt.setGenCount(genCount);

		runXTimes(gt, 10, fileStream, i);
	}
}

void Controller::testMaxTreeSize(GeneticController gt, double min, double max, double step)
{
	ofstream fileStream;
	string filename = "results/treeSizeTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		int treeSize = i;
		gt.setTreeHeight(treeSize);

		runXTimes(gt, 10, fileStream, i);
	}
}

void Controller::testCrossChance(GeneticController gt, double min, double max, double step)
{
	ofstream fileStream;
	string filename = "results/crossingTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		double crossingChance = i;
		gt.setCrossingChance(crossingChance);

		runXTimes(gt, 10, fileStream, i);
	}
}

void Controller::testTourneySize(GeneticController gt, double min, double max, double step)
{
	ofstream fileStream;
	string filename = "results/tourneyTestResults.csv";
	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		double tourneySize = i;
		gt.setTourneySize(tourneySize);

		runXTimes(gt, 10, fileStream, i);
	}
}

void Controller::testParams(GeneticController & gt)
{
	//testPopSize(gt, 20, 500, 50);
	//testGenCount(gt, 5, 500, 50);
	testTourneySize(gt, 0.1, 0.5, 0.05);
	testCrossChance(gt, 0, 1, 0.1);
	//testMaxTreeSize(gt, 2, 8, 1);
	//testMutation(gt, 0.05, 0.05, 0.05);
}

void Controller::runXTimes(GeneticController & gt, int count, ofstream& fileStream, double testedValue)
{
	Backtester bt;
	list<int> gains;
	list<int> transactionCounts;
	auto startTime = chrono::high_resolution_clock::now();
	for (int j = 0; j < 10; j++)
	{
		auto spec = gt.startEvolution();

		Backtester::TransactionData td = bt.backtest(*gt.getDataSet(), spec.get());
		gains.push_back(td.getTotalPipGain());
		transactionCounts.push_back(td.getTransactionCount());
		gt.reset();
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto time = endTime - startTime;

	double gainsSum = accumulate(begin(gains), end(gains), 0.0);
	double transactionCountSum = accumulate(begin(transactionCounts), end(transactionCounts), 0.0);
	fileStream << testedValue << ";" << gainsSum / 10 << ";" << countStandardDeviation(gains) << ";" << transactionCountSum / 10 << ";" << countStandardDeviation(transactionCounts) << ";" << chrono::duration_cast<chrono::seconds>(time).count() / 10 << endl;
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

	indicators.addIndicator(shared_ptr<Indicator>(new RateOfChange(3)));
	indicators.addIndicator(shared_ptr<Indicator>(new RateOfChange(12)));

	indicators.addIndicator(shared_ptr<Indicator>(new MovingAverageResistance(1, 3, 12, true)));
	indicators.addIndicator(shared_ptr<Indicator>(new MovingAverageResistance(2, 3, 12, true)));
	indicators.addIndicator(shared_ptr<Indicator>(new MovingAverageResistance(3, 3, 12, true)));

	indicators.addIndicator(shared_ptr<Indicator>(new MovingAverageResistance(1, 3, 12, false)));
	indicators.addIndicator(shared_ptr<Indicator>(new MovingAverageResistance(2, 3, 12, false)));
	indicators.addIndicator(shared_ptr<Indicator>(new MovingAverageResistance(3, 3, 12, false)));

	indicators.addIndicator(shared_ptr<Indicator>(new PastPricesTrendLine(true)));
	indicators.addIndicator(shared_ptr<Indicator>(new PastPricesTrendLine(false)));

	//indicators.addIndicator(shared_ptr<Indicator>(new RelativeStrengthIndex(14)));

	data.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.01.2016 00:00:00"), DateTime("15.01.2016 00:00:00"), indicators);
	DataSet data2;
	data2.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("15.01.2016 00:00:00"), DateTime("30.01.2016 00:00:00"), indicators);
	MutationChances *mc = new MutationChances(0.05, 0.1, 0.05, 0.05);
	//MutationChances *mc = new MutationChances(0.05);
	GeneticController gt(0.4, 0.05, *mc, indicators, data, 5, 200, 100);

	Controller ct;
	//ct.testParams(gt);
	
	Backtester bt;
	shared_ptr<Specimen> best = gt.startEvolution();
	//Backtester::TransactionData td = bt.backtest(*gt.getDataSet(), best.get());
	Backtester::TransactionData td = bt.backtest(data2, best.get());
	cout << td.getTransactionCount();
	cout << best->toLatex();

	return 0;
}

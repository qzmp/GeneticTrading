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

vector<double> Controller::countQuartiles(list<int>& values)
{
	values.sort();
	double firstQuartile, secondQuartile, thirdQuartile;
	secondQuartile = countMedian(values);

	int middle = values.size() % 2 == 0 ? values.size() / 2 - 1 : values.size() / 2;
	auto end = next(values.begin(), middle);

	list<int> firstHalf(values.begin(), end);
	if (values.size() % 2 == 0)
	{
		end++;
	}
	list<int> secondHalf(end, values.end());

	firstQuartile = countMedian(firstHalf);
	thirdQuartile = countMedian(secondHalf);

	return { firstQuartile, secondQuartile, thirdQuartile };
}

double Controller::countMedian(list<int>& values)
{
	list<int>::iterator it = values.begin();
	for (int i = 1; i < values.size() / 2; i++)
	{
		it++;
	}
	if (values.size() % 2 != 0)
	{
		it++;
		return *it;
	}
	else
	{
		int middleLeft = *it;
		it++;
		int middleRight = *it;
		return (middleLeft + middleRight) / 2.0;
	}
}

Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::testMutation(GeneticController gt, double min, double max, double step, DataSet & testingSet)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/mutationTesting.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		MutationChances mc(i);
		gt.setMutationChances(mc);

		string filePrefix = "results/mutationTesting/" + to_string(i);
		test2(gt, filePrefix, filestream);
	}
}

void Controller::testPopSize(GeneticController gt, double min, double max, double step, DataSet & testingSet)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/popSizeTesting.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		int popSize = i;
		gt.setPopSize(popSize);

		string filePrefix = "popSizeTesting/" + to_string(i);
		test2(gt, filePrefix, filestream);
	}
}

void Controller::testGenCount(GeneticController gt, double min, double max, double step, DataSet & testingSet)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/genCountTesting.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		int genCount = i;
		gt.setGenCount(genCount);

		string filePrefix = "genCountTesting/" + to_string(i);
		test2(gt, filePrefix, filestream);
	}
}

void Controller::testMaxTreeSize(GeneticController gt, double min, double max, double step, DataSet & testingSet)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/treeSizeTesting.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		int treeSize = i;
		gt.setTreeHeight(treeSize);

		string filePrefix = "treeSizeTesting/" + to_string(i);
		test2(gt, filePrefix, filestream);
	}
}

void Controller::testCrossChance(GeneticController gt, double min, double max, double step, DataSet & testingSet)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/crossTesting.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		double crossingChance = i;
		gt.setCrossingChance(crossingChance);

		string filePrefix = "crossChanceTesting/" + to_string(i);
		test2(gt, filePrefix, filestream);
	}
}

void Controller::testTourneySize(GeneticController gt, double min, double max, double step, DataSet & testingSet)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/tourneyTesting.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = min; i <= max; i += step)
	{
		double tourneySize = i;
		gt.setTourneySize(tourneySize);

		string filePrefix = "tourneyTesting/" + to_string(i);
		test2(gt, filePrefix, filestream);
	}
}

void Controller::testParams(GeneticController & gt, DataSet & testingSet)
{
	//testPopSize(gt, 20, 500, 100, testingSet);
	//testGenCount(gt, 5, 500, 100, testingSet);
	//testTourneySize(gt, 0.01, 0.5, 0.1, testingSet);
	//testCrossChance(gt, 0, 1, 0.2, testingSet);
	//testMaxTreeSize(gt, 3, 3, 2, testingSet);
	testMutation(gt, 0, 0.1, 0.02, testingSet);
}

vector<DataSet> Controller::getDataSets(IndicatorHolder & indicators)
{
	vector<DataSet> dataSets(24);
	for (int i = 1; i <= 12; i++)
	{
		dataSets[2 * i - 2].loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.07.2015-31.12.2016.csv"), DateTime(1, i, 2016), DateTime(15, i, 2016), indicators);
		dataSets[2 * i - 1].loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.07.2015-31.12.2016.csv"), DateTime(15, i, 2016), DateTime(1, i + 1, 2016), indicators);
	}
	return dataSets;
}

void Controller::testDataSets(GeneticController & gt, vector<DataSet>& dataSets)
{
	ofstream fileStream;
	string filename = "results/testing.csv";

	fileStream.imbue(locale());
	fileStream.open(filename, ios::ate | ios_base::app);

	Backtester bt;
	double pipSum = 0;
	double transactionSum = 0;
	for (double i = 0; i < dataSets.size(); i++)
	{
		gt.setDataSet(dataSets[i]);
		vector<DataSet> dataSets2 = dataSets;
		dataSets2.erase(dataSets2.begin() + i);
		testDataSet(gt, dataSets2, fileStream);
	}
}

void Controller::testDataSet(GeneticController & gt, vector<DataSet> & dataSets, ofstream & filestream)
{
	Backtester bt;

	auto spec = gt.startEvolution();
	Backtester::TransactionData td = bt.backtest(*gt.getDataSet(), spec.get());
	filestream << td.getPipGainWithProvision(20) << endl;

	list<int> testingGains;
	list<int> testingPositive;
	list<int> testingNegative;
	double testPosTransactions = 0;
	double testNegTransactions = 0;
	list<int> testingTransactionCounts;

	for (int i = 0; i < dataSets.size() - 1; i++)
	{

		td = bt.backtest(dataSets[i], spec.get());

		filestream << td.getPipGainWithProvision(20);

		testingGains.push_back(td.getPipGainWithProvision(20));
		testingPositive.push_back(td.getGains());
		testingNegative.push_back(td.getLosses());
		testPosTransactions += td.getGoodTransactionCount();
		testNegTransactions += td.getBadTransactionCount();
		testingTransactionCounts.push_back(td.getTransactionCount());
	}

	double testingGainsSum = accumulate(begin(testingGains), end(testingGains), 0.0);
	double testingPosSum = accumulate(begin(testingPositive), end(testingPositive), 0.0);
	double testingNegSum = accumulate(begin(testingNegative), end(testingNegative), 0.0);
	double testingTransactionCountSum = accumulate(begin(testingTransactionCounts), end(testingTransactionCounts), 0.0);

	vector<double> testQuartiles = countQuartiles(testingGains);

	filestream << ";;;" << testingGainsSum / dataSets.size() << ";" << countStandardDeviation(testingGains)
		<< ";" << testingPosSum / dataSets.size() << ";" << testingNegSum / dataSets.size()
		<< ";" << testPosTransactions / dataSets.size() << ";" << testNegTransactions / dataSets.size()
		<< ";" << testingTransactionCountSum / dataSets.size() << ";" << countStandardDeviation(testingTransactionCounts)

		<< ";"

		<< ";" << *min_element(testingGains.begin(), testingGains.end())
		<< ";" << testQuartiles[0] << ";" << testQuartiles[1]
		<< ";" << testQuartiles[2] << ";" << *max_element(testingGains.begin(), testingGains.end()) << endl;
}

void Controller::runXTimes(GeneticController & gt, int count, ofstream& fileStream, double testedValue, DataSet & testingSet)
{
	Backtester bt;
	list<int> gains;
	list<int> positive;
	list<int> negative;
	double posTransactions = 0;
	double negTransactions = 0;

	list<int> transactionCounts;

	list<int> testingGains;
	list<int> testingPositive;
	list<int> testingNegative;
	double testPosTransactions = 0;
	double testNegTransactions = 0;
	list<int> testingTransactionCounts;
	auto startTime = chrono::high_resolution_clock::now();
	for (int j = 0; j < count; j++)
	{
		auto spec = gt.startEvolution();

		Backtester::TransactionData td = bt.backtest(*gt.getDataSet(), spec.get());
		gains.push_back(td.getPipGainWithProvision(20));
		positive.push_back(td.getGains());
		negative.push_back(td.getLosses());
		posTransactions += td.getGoodTransactionCount();
		negTransactions += td.getBadTransactionCount();
		transactionCounts.push_back(td.getTransactionCount());

		td = bt.backtest(testingSet, spec.get());
		testingGains.push_back(td.getPipGainWithProvision(20));
		testingPositive.push_back(td.getGains());
		testingNegative.push_back(td.getLosses());
		testPosTransactions += td.getGoodTransactionCount();
		testNegTransactions += td.getBadTransactionCount();
		testingTransactionCounts.push_back(td.getTransactionCount());

		gt.reset();
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto time = endTime - startTime;

	double gainsSum = accumulate(begin(gains), end(gains), 0.0);
	double posSum = accumulate(begin(positive), end(positive), 0.0);
	double negSum = accumulate(begin(negative), end(negative), 0.0);
	double transactionCountSum = accumulate(begin(transactionCounts), end(transactionCounts), 0.0);

	double testingGainsSum = accumulate(begin(testingGains), end(testingGains), 0.0);
	double testingPosSum = accumulate(begin(testingPositive), end(testingPositive), 0.0);
	double testingNegSum = accumulate(begin(testingNegative), end(testingNegative), 0.0);
	double testingTransactionCountSum = accumulate(begin(testingTransactionCounts), end(testingTransactionCounts), 0.0);

	vector<double> trainQuartiles = countQuartiles(gains);
	vector<double> testQuartiles = countQuartiles(testingGains);

	fileStream << testedValue << ";" << gainsSum / count << ";" << countStandardDeviation(gains)
		<< ";" << posSum / count << ";" << negSum / count
		<< ";" << transactionCountSum / count << ";" << countStandardDeviation(transactionCounts)
		<< ";" << posTransactions / count << ";" << negTransactions

		<< ";"
		
		<< ";" << *min_element(gains.begin(), gains.end())
		<< ";" << trainQuartiles[0] << ";" << trainQuartiles[1]
		<< ";" << trainQuartiles[2] << ";" << *max_element(gains.begin(), gains.end())

		<< ";"

		<< ";" << testingGainsSum / count << ";" << countStandardDeviation(testingGains)
		<< ";" << testingPosSum / count << ";" << testingNegSum / count
		<< ";" << testPosTransactions / count << ";" << testNegTransactions
		<< ";" << testingTransactionCountSum / count << ";" << countStandardDeviation(testingTransactionCounts)

		<< ";"

		<< ";" << *min_element(testingGains.begin(), testingGains.end())
		<< ";" << testQuartiles[0] << ";" << testQuartiles[1]
		<< ";" << testQuartiles[2] << ";" << *max_element(testingGains.begin(), testingGains.end())

		<< ";"

		<< ";" << chrono::duration_cast<chrono::seconds>(time).count() / count << endl;
}

void Controller::test2(GeneticController &gt, string & filePrefix, ofstream & summaryStream)
{
	summaryStream << endl;
	for (int i = 0; i < 3; i++)
	{
		gt.setDataSet(trainingSet[i]);
		runXTimes2(gt, 200, testingSets[i], filePrefix, summaryStream);
		summaryStream << endl;
	}
}

void Controller::runXTimes2(GeneticController & gt, int count, vector<DataSet> & testingSets, string & filePrefix, ofstream & summaryFile)
{
	Backtester bt;


	list<int> gains;
	list<int> positive;
	list<int> negative;
	double posTransactions = 0;
	double negTransactions = 0;

	list<int> transactionCounts;

	vector<list<int>> noProvGains(3);
	vector<list<int>> testingGains(3);
	vector<list<int>> testingPositive(3);
	vector<list<int>> testingNegative(3);
	vector<double> testPosTransactions = { 0, 0, 0 };
	vector<double> testNegTransactions = { 0, 0, 0 };
	vector<list<int>> testingTransactionCounts(3);

	auto startTime = chrono::high_resolution_clock::now();


	ofstream filestream;
	filestream.imbue(locale());
	string filename = filePrefix + ".csv";
	filestream.open(filename, ios::ate | ios_base::app);
	filestream << endl << gt.getDataSet()->getName();

	for (int j = 0; j < testingSets.size(); j++)
	{
		filestream << ";;;;;" << testingSets[j].getName();
	}
	filestream << endl;

	for (int i = 0; i < count; i++)
	{
		auto spec = gt.startEvolution();

		Backtester::TransactionData td = bt.backtest(*gt.getDataSet(), spec.get());
		filestream << td.getTotalPipGain() << ";"
			<< td.getPipGainWithProvision(20) << ";"
			<< td.getGoodTransactionCount() << ";"
			<< td.getBadTransactionCount() << ";;";

		gains.push_back(td.getPipGainWithProvision(20));

		for (int j = 0; j < testingSets.size(); j++)
		{

			td = bt.backtest(testingSets[j], spec.get());

			noProvGains[j].push_back(td.getPipGainWithProvision(0));
			testingGains[j].push_back(td.getPipGainWithProvision(20));
			testingPositive[j].push_back(td.getGains());
			testingNegative[j].push_back(td.getLosses());
			testPosTransactions[j] += td.getGoodTransactionCount();
			testNegTransactions[j] += td.getBadTransactionCount();
			testingTransactionCounts[j].push_back(td.getTransactionCount());

			filestream << td.getTotalPipGain() << ";"
				<< td.getPipGainWithProvision(20) << ";"
				<< td.getGoodTransactionCount() << ";"
				<< td.getBadTransactionCount() << ";;";
		}
		filestream << endl;

		gt.reset();
	}
	double trainingGainsSum = accumulate(begin(gains), end(gains), 0.0);

	summaryFile << trainingGainsSum / count << ";" << countStandardDeviation(gains) << ";";
	for (int i = 0; i < 3; i++) {

		double noProvGainsSum = accumulate(begin(noProvGains[i]), end(noProvGains[i]), 0.0);
		double testingGainsSum = accumulate(begin(testingGains[i]), end(testingGains[i]), 0.0);
		double testingPosSum = accumulate(begin(testingPositive[i]), end(testingPositive[i]), 0.0);
		double testingNegSum = accumulate(begin(testingNegative[i]), end(testingNegative[i]), 0.0);
		double testingTransactionCountSum = accumulate(begin(testingTransactionCounts[i]), end(testingTransactionCounts[i]), 0.0);

		vector<double> testQuartiles = countQuartiles(testingGains[i]);

		summaryFile << ";" << noProvGainsSum / count << ";" << testingGainsSum / count << ";" << countStandardDeviation(testingGains[i])
			<< ";" << testingPosSum / count << ";" << testingNegSum / count
			<< ";" << testPosTransactions[i] / count << ";" << testNegTransactions[i] / count
			<< ";" << testingTransactionCountSum / count << ";" << countStandardDeviation(testingTransactionCounts[i])

			<< ";" << *min_element(testingGains[i].begin(), testingGains[i].end())
			<< ";" << testQuartiles[0] << ";" << testQuartiles[1]
			<< ";" << testQuartiles[2] << ";" << *max_element(testingGains[i].begin(), testingGains[i].end())
			<< ";";
	}
	
}

void Controller::trainingSetSizeTest(GeneticController & gt, IndicatorHolder & indicators)
{
	ofstream filestream;
	filestream.imbue(locale());
	string filename = "results/trainingSetSize.csv";
	filestream.open(filename, ios::ate | ios_base::app);

	for (int i = 8; i > 7; i--)
	{
		string filePrefix = to_string(13 - i);
		DataSet data0;
		data0.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("15." + to_string(i) + ".2015 00:00:00"), DateTime("15.01.2016 00:00:00"), indicators);
		gt.setDataSet(data0);
		runXTimes2(gt, 200, testingSets[0], filePrefix, filestream);
		filestream << endl;
	}
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

	DataSet data0;
	data0.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.01.2016 00:00:00"), DateTime("15.01.2016 00:00:00"), indicators);
	DataSet data1;
	data1.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("15.01.2016 00:00:00"), DateTime("1.02.2016 00:00:00"), indicators);
	DataSet data2;
	data2.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.02.2016 00:00:00"), DateTime("15.02.2016 00:00:00"), indicators);
	DataSet data3;
	data3.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("15.02.2016 00:00:00"), DateTime("1.03.2016 00:00:00"), indicators);
	DataSet data4;
	data4.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("01.03.2016 00:00:00"), DateTime("15.03.2016 00:00:00"), indicators);
	DataSet data5;
	data5.loadData(string("Data/EURUSD_Candlestick_10_m_BID_01.01.2007_10.12.2016.csv"), DateTime("15.03.2016 00:00:00"), DateTime("1.04.2016 00:00:00"), indicators);

	vector<DataSet> testingSet1 = { data1, data2, data3 };
	vector<DataSet> testingSet2 = { data2, data3, data4 };
	vector<DataSet> testingSet3 = { data3, data4, data5 };
	
	MutationChances *mc = new MutationChances(0.05, 0.05, 0.05, 0.05);
	//MutationChances *mc = new MutationChances(0);
	GeneticController gt(0.1, 0.4, *mc, indicators, data, 4, 100, 100);

	Controller ct;
	ct.testingSets = { testingSet1, testingSet2, testingSet3 };
	ct.trainingSet = { data0, data1, data2 };

	//ct.testParams(gt, data2);

	ct.trainingSetSizeTest(gt, indicators);

	//ct.runXTimes2(gt, 250, testingSets);

	//ct.testDataSets(gt, ct.getDataSets(indicators));
	
	Backtester bt;
	//shared_ptr<Specimen> best = gt.startEvolution();
	/*Backtester::TransactionData td = bt.backtest(*gt.getDataSet(), best.get());
	Backtester::TransactionData td = bt.backtest(data2, best.get());
	cout << td.getTransactionCount();
	cout << best->toLatex();*/

	return 0;
}

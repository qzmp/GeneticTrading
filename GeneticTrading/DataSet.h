#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "DateTime.h"
#include "IndicatorHolder.h"

using namespace std;

class DataSet
{
	DateTime start;
	DateTime end;

	vector<DateTime> timeStamps;
	vector<double> openPrices;
	vector<double> closePrices;
	vector<double> highPrices;
	vector<double> lowPrices;
	map<shared_ptr<Indicator>, vector<double>> indicators;

	IndicatorHolder indicatorHolder;

	int getNeededLinesCount();
	void saveLine(istringstream & ss);
	void countIndicators(list<double> & lastClosePrices);

	int findStartIndex(string & filename, DateTime & start);

public:
	DataSet();
	~DataSet();

	int loadData(string & filename, DateTime & start, DateTime & end, IndicatorHolder & indicatorObjects);

	int getSize();

	double getOpenPrice(int index);
	double getClosePrice(int index);
	double getHighPrice(int index);
	double getLowPrice(int index);
	map<shared_ptr<Indicator>, double> getIndicatorValues(int index);

	DateTime getStart();
	DateTime getEnd();

};


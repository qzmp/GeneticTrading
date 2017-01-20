#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "DateTime.h"
#include "Indicator.h"

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

	vector<shared_ptr<Indicator>> indicatorObjects;

	int getNeededLinesCount();
	void saveLine(istringstream & ss);
	void countIndicators(list<double> & lastClosePrices);

	int findStartIndex(string & filename, DateTime & start);

public:
	DataSet();
	~DataSet();

	int loadData(string & filename, DateTime & start, DateTime & end, vector<shared_ptr<Indicator>> & indicatorObjects);

	int getSize();

	double getOpenPrice(int index);
	double getClosePrice(int index);
	double getHighPrice(int index);
	double getLowPrice(int index);
	map<shared_ptr<Indicator>, double> getIndicatorValues(int index);

	DateTime getStart();
	DateTime getEnd();

};


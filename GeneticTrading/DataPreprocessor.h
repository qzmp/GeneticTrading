#pragma once

#include "Indicator.h"
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

class DataPreprocessor
{
private:
	list<shared_ptr<Indicator>> indicators;
	list<double> closePrices;

	int addHeaders(string currentHeaders, list<shared_ptr<Indicator>>& indicators, ofstream & outputStream);
	void addIndicatorValues(ofstream& outputStream);
public:
	DataPreprocessor(list<shared_ptr<Indicator>>& indicators);
	~DataPreprocessor();

	int addIndicators(string fileName);
};

